#include "connection.hpp"
#include <utility>
#include <vector>
#include "connection_manager.hpp"
#include "request_handler.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>

#include "request_handler.hpp"

namespace dem1 {
	namespace server {

		connection::connection(boost::asio::ip::tcp::socket socket,
			connection_manager& manager)
			: socket_(std::move(socket)),
			connection_manager_(manager),
			incoming_buf_size_(64*1024),
			is_close_flag_(false),
			session_id_(boost::uuids::to_string(boost::uuids::random_generator()())) {

			incoming_buf_.buffer = new char[incoming_buf_size_];
			incoming_buf_.buffer_len = incoming_buf_size_;	

			
			socket_.non_blocking(true);
			
		}

		connection::~connection()
		{
            Log::Debug("dem1service:: connection::~connection()\n");

			if (incoming_buf_.buffer) {
				delete[] incoming_buf_.buffer;
			}

		}


		void connection::start() 
        {
			is_close_flag_ = false;
            auto self(shared_from_this());
			Log::Debug("dem1service:: add connection %s \n", session_id_.c_str());
            int ret = request_handler_.start(self);
			if (ret == -1)
            {
				Log::Error("dem1service:: request_handler_ start Failed %s", session_id_.c_str());
				this->stop();
				return;
			}
			do_read();
		}

		void connection::stop()
        {
			if (is_close_flag_ == false)
			{
				is_close_flag_ = true;
				auto self(shared_from_this());
				Log::Debug("dem1service:: stop connection %s \n", session_id_.c_str());
				request_handler_.stop();
				socket_.shutdown(boost::asio::socket_base::shutdown_type::shutdown_both);
				socket_.close();
			}
            
		}


		std::string  connection::get_sessionid(){
			return session_id_;
		}

		void connection::do_read() 
        {
			auto self(shared_from_this());

			incoming_buf_.buffer_offset = 0;
			memset(incoming_buf_.buffer, 0, incoming_buf_size_);

			this->set_timeout(SOCKET_TIMEOUT);

			int header_len = sizeof(protocol_head_t);
			boost::asio::async_read(socket_,
				boost::asio::buffer(incoming_buf_.buffer, header_len),
				boost::bind(&connection::handle_msg_length,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred)
				);
		}
		//
		// message frame
		//
		// +--------+------------+--------------+
		// | length | message body |
		// +--------+------------+--------------+
		//

		void connection::handle_msg_length(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			this->cancel_timeout();
			auto self(shared_from_this());
			if (!error) 
            {
				incoming_buf_.buffer_offset = 0;
				incoming_buf_.buffer_len = sizeof(protocol_head_t);
				prot_head_.read(&incoming_buf_);

				Log::Info("dem1service:: handle_msg_length::prot_head_.CMD:   %d ", prot_head_.nCmd);

                if (prot_head_.nStartFlags == 0xAF && prot_head_.nEndFlags == 0xFA)
				{
                    ensure_incoming_buf_capa((prot_head_.nDataLen));
                    memset(incoming_buf_.buffer, 0, incoming_buf_size_);


					this->set_timeout(SOCKET_TIMEOUT);
                    boost::asio::async_read(socket_,
                        boost::asio::buffer(incoming_buf_.buffer, (prot_head_.nDataLen)),
                        boost::bind(&connection::handle_msg_body,
                        shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred)
                        );               
				}
				else
                {
					do_read(); // handle other messages..
				}
			}
			else if (error != boost::asio::error::operation_aborted)
            {
				Log::Info("dem1service:: handle_msg_length::error:    error_code  code %d msg %s", error.value(), error.message().c_str());
				connection_manager_.stop(shared_from_this());
			}
		}

		void connection::handle_msg_body(const boost::system::error_code& error,
			size_t bytes_transferred)
		{
			this->cancel_timeout();
			auto self(shared_from_this());
			if (!error) 
            {
             //   Log::Info("dem1service:: handle_msg_body len %d result %d \n", prot_head_.nDataLen, prot_head_.nResult);
				//³õÊ¼»¯
				incoming_buf_.buffer_offset = 0;
				incoming_buf_.buffer_len = prot_head_.nDataLen;
      
				APIProtocal_Handler(&prot_head_, &incoming_buf_, &request_handler_, session_id_);

                this->do_read();

			}
			else if (error != boost::asio::error::operation_aborted) 
            {
   
				Log::Info("dem1service:: handle_msg_body::error:    error_code  code %d msg %s", error.value(), error.message().c_str());

				connection_manager_.stop(shared_from_this());
			}
		}

		void  connection::ensure_incoming_buf_capa(size_t required_size)
		{
			size_t orig_size = incoming_buf_size_;
			while (incoming_buf_size_ < required_size) {
				incoming_buf_size_ *= 2;
			}

			if (orig_size != incoming_buf_size_) {
				delete[] incoming_buf_.buffer;
				incoming_buf_.buffer = new char[incoming_buf_size_];
				incoming_buf_.buffer_len = incoming_buf_size_;
			}
		}

		void connection::do_write(response& res) 
        {
            if (!this )
            {
                return;
            }

			this->set_timeout(SOCKET_TIMEOUT);


			std::vector<boost::asio::const_buffer> buffer = res.to_buffers();
            std::shared_ptr<connection> self = shared_from_this();
            boost::asio::async_write(socket_, buffer,
                [this, self](boost::system::error_code ec, std::size_t n)
            {
				this->cancel_timeout();

                if (!ec) 
                {
					Log::Debug("dem1service:: boost::asio::async_write Send Success   size %d \n\n", n);
                }
                else if (ec != boost::asio::error::operation_aborted) 
                {
                    Log::Error("dem1service:: boost::asio::async_write start  size_t %d",n);
					Log::Error("dem1service:: boost::asio::async_write start  error_code  code %d msg %s", ec.value(), ec.message().c_str());
					 if (self)
                    {
                        connection_manager_.stop(self);
                    }
					Log::Error("dem1service:: boost::asio::async_write end size_t %d", n);

                }
            });
         
		}


		void  connection::set_timeout(long seconds) {
			if (seconds == 0) {
				timer_ = nullptr;
				return;
			}
			
			std::shared_ptr<connection> self = shared_from_this();
			boost::asio::io_service &socket_ser = socket_.get_io_service();
			std::shared_ptr<boost::asio::deadline_timer> timer_;


			timer_.reset(new boost::asio::deadline_timer(socket_ser));
			timer_->expires_from_now(boost::posix_time::seconds(seconds));
			timer_->async_wait([this,self](const boost::system::error_code &ec) {
				if (!ec){
					Log::Debug("dem1service:: timer_->async_wait Stop");
					if (self)
					{
						connection_manager_.stop(self);
					}
				}
				
			});
		}

		void  connection::cancel_timeout() {
			if (timer_) {
				try
				{
					timer_->cancel();
				}
				catch (boost::system::system_error e)
				{
					
				}
			
				
			}
		}

		void connection::handle_msg_json(const boost::system::error_code& error, size_t bytes_transferred)
		{
			int recv_length = incoming_buf_.buffer_len;
			this->cancel_timeout();
			auto self(shared_from_this());
			if (!error)
			{
				bool result = strstr(incoming_buf_.buffer, "\r\n\r\n");
				if (result)
				{
					std::string header = incoming_buf_.buffer;
					header = header.substr(0, header.find("\r\n\r\n", 0));

					std::string tmp = header.substr(header.find("Content-Length:", 0) + strlen("Content-Length:"));
					tmp = tmp.substr(0, tmp.find("\r\n", 0));
					int content_length = ::atoi(tmp.c_str());

					int expect_length = content_length - (incoming_buf_.buffer_len - header.length()) + 4;
					Log::Info("dem1service:: content_length:%d, expect_length:%d.\n", content_length, expect_length);

					while (expect_length > 0)
					{
						int ret = socket_.receive(boost::asio::buffer(incoming_buf_.buffer + recv_length, (expect_length)));
						if (ret == -1)
						{
							Log::Info("dem1service:: socket recv error.\n");
							return;
						}
						recv_length += ret;
						expect_length -= ret;
					}

					std::string message = incoming_buf_.buffer;
					Log::Info("dem1service:: message:%s", message.c_str());

					this->do_read();
				}

			}
			else if (error != boost::asio::error::operation_aborted)
			{

				Log::Info("dem1service:: handle_msg_body::error:    error_code  code %d msg %s", error.value(), error.message().c_str());

				connection_manager_.stop(shared_from_this());
			}
		}


    }  // namespace server
}  // namespace dem1
