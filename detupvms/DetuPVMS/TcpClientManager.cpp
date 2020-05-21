#include <iostream>
#include <boost/algorithm/string.hpp>

#include "TcpClientManager.hpp"
#include "MessageManager.h"


namespace dem1 {
	namespace client {
		using boost::asio::ip::tcp;

		TcpClientManager::TcpClientManager()
		{

		}

		void TcpClientManager::init(const std::string& address, uint16_t port)
        {
			is_tcp_closed_ = false;
			address_ = address;
			port_ = port;
			incoming_buf_size_ = 1024;

            incoming_buf_.buffer = new char[incoming_buf_size_];
			incoming_buf_.buffer_len = incoming_buf_size_;

			// Get a list of endpoints corresponding to the server name.
			tcp::resolver resolver(io_service_);
			tcp::resolver::query query(address_, std::to_string(port_));
			tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
			tcp::resolver::iterator end;

			// Try each endpoint until we successfully establish a connection.
			boost::system::error_code error = boost::asio::error::host_not_found;
			while (error && endpoint_iterator != end) 
            {
				socket_.close();
				socket_.connect(*endpoint_iterator++, error);
			}

			if (error) 
            {
				printf("err %s",error.message().c_str());
				emit DetuClientLoginFailed();
				return;
			}
			//emit DetuClientLoginOk();
			io_service_.run();
		}

		void TcpClientManager::sendData(protocol_head_t api_head, api_detu_client_request_video_t api_detu)
        {
            printf("sendData >> \n");
            api_head.nDataLen = sizeof(api_detu);

            int msg_len = sizeof(api_head) + sizeof(api_detu);

            netbuffer netbuf;
            netbuf.buffer = (char*)malloc(msg_len);
            memset(netbuf.buffer, 0, msg_len * sizeof(char));

            api_head.write(&netbuf);
            api_detu.write(&netbuf);

            //boost::asio::detail::function<void()> debug_check;
            std::vector<boost::asio::const_buffer> buffers;
            //buffers.push_back(boost::asio::const_buffer(netbuf.buffer, msg_len, debug_check));
            buffers.push_back(boost::asio::const_buffer(netbuf.buffer, msg_len));
            boost::asio::write(socket_, buffers);

            free(netbuf.buffer);
        }

		void TcpClientManager::sendData(protocol_head_t api_head, api_register_t api_reg)
        {
			printf("sendData >> \n");
			api_head.nDataLen = sizeof(api_reg);

			int msg_len = sizeof(api_head) + sizeof(api_reg);

			netbuffer netbuf;
			netbuf.buffer = (char*)malloc(msg_len);
			memset(netbuf.buffer, 0, msg_len * sizeof(char));

			api_head.write(&netbuf);
			api_reg.write(&netbuf);

			std::vector<boost::asio::const_buffer> buffers;

            buffers.push_back(boost::asio::const_buffer(netbuf.buffer, msg_len));
			boost::asio::write(socket_, buffers);
	
			free(netbuf.buffer);
		}

		void TcpClientManager::do_read() 
		{
			//auto self(shared_from_this());
			incoming_buf_.buffer_offset = 0;
			memset(incoming_buf_.buffer, 0, incoming_buf_.buffer_len);

			int header_len = sizeof(protocol_head_t);
			boost::asio::async_read(socket_,
				boost::asio::buffer(incoming_buf_.buffer, header_len),
				boost::bind(&TcpClientManager::handle_msg_length,
				this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
				);
		}

		void TcpClientManager::handle_msg_length(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			if (!error)
			{
				incoming_buf_.buffer_offset = 0;
				incoming_buf_.buffer_len = sizeof(protocol_head_t);
				prot_head_.read(&incoming_buf_);
				if (prot_head_.nStartFlags == 0xAF && prot_head_.nEndFlags == 0xFA)
				{
					ensure_incoming_buf_capa((prot_head_.nDataLen));
					memset(incoming_buf_.buffer, 0, incoming_buf_size_);

					boost::asio::async_read(socket_,
						boost::asio::buffer(incoming_buf_.buffer, (prot_head_.nDataLen)),
						boost::bind(&TcpClientManager::handle_msg_body,
						this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred)
						);
				}
				else
				{
					std::cout << "handle_msg_length error nStartFlags = " << prot_head_.nStartFlags << std::endl;
					do_read(); // handle other messages..
				}
			}
			else if (error != boost::asio::error::operation_aborted)
			{
				//待处理
				//connection_manager_.stop(shared_from_this());
			}
		}

		void TcpClientManager::handle_msg_body(const boost::system::error_code& error, size_t bytes_transferred)
		{
			//auto self(shared_from_this());
			if (!error)
			{
				Log::Debug("handle_msg_body len %d result %d \n", prot_head_.nDataLen, prot_head_.nResult);

				//初始化
				incoming_buf_.buffer_offset = 0;
				incoming_buf_.buffer_len = prot_head_.nDataLen;

				bool invalid_msg_id = false;
				switch (prot_head_.nCmd)
				{
				case CMD_REQUEST_LIVE_VIDEO_RES:

					break;
				case CMD_DETU_CLIENT_REGISTER_RES:
					Log::Debug("api_head type %d \n", prot_head_.nCmd);
					api_reg_res_.read(&incoming_buf_);
					std::cout << "api size = " << api_reg_res_.numlist << std::endl;

					emit NvrListReceived();
					break;

				default:
					invalid_msg_id = true;
					std::cout << "invalid message id = " << prot_head_.nCmd << std::endl;
					break;
				}

				//APIProtocal_Handler(prot_head_.nCmd, &incoming_buf_, &request_handler_);

				this->do_read();

			}
			else if (error != boost::asio::error::operation_aborted) 
			{
				//待处理
				//connection_manager_.stop(shared_from_this());
			}
		}

		void TcpClientManager::SetMainWindow(DetuPVMS* main_window)
		{
			mainwindow_ = main_window;
		}

		void TcpClientManager::close()
		{
			do_read_mutx_.lock();
			is_tcp_closed_ = true;
			do_read_mutx_.unlock();

			Sleep(1000);

			socket_.close();
		}

		void  TcpClientManager::ensure_incoming_buf_capa(size_t required_size)
		{
			size_t orig_size = incoming_buf_size_;
			while (incoming_buf_size_ < required_size) {
				incoming_buf_size_ *= 2;
			}

			if (orig_size != incoming_buf_size_) {
				delete[] incoming_buf_.buffer;
				incoming_buf_.buffer = new char[incoming_buf_size_];
			}
		}


	}  // namespace client
}  // namespace 
