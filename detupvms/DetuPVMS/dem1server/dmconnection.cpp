#include "dmconnection.hpp"
#include <utility>
#include <vector>


#include "request_handler.hpp"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/bind.hpp>



#include "APIProtocolHandler.h"

namespace dm {
    namespace server {
        
        dmconnection::dmconnection(boost::asio::ip::tcp::socket socket)
        : socket_(std::move(socket)),
        request_handler_(),
        incoming_buf_size_(2000000),
        session_id_(boost::uuids::to_string(boost::uuids::random_generator()())) {
            
            incoming_buf_.buffer = new char[incoming_buf_size_];
            incoming_buf_.buffer_len = incoming_buf_size_;

		
			socket_state_ = SOCKETSTATE_FAILED;
        }
        
        dmconnection::~dmconnection()
        {
			this->close();
            
        }

		void dmconnection::close(){
			if (is_close_flag_ == false)
			{
				is_close_flag_ = true;


				if (incoming_buf_.buffer) {
					delete[] incoming_buf_.buffer;
					incoming_buf_.buffer = NULL;
				}
			}

		}
        

		SOCKETSTATE_ENUM dmconnection::get_socketstate(){

			return socket_state_;

		}
        
        void dmconnection::start() {
            
			socket_closed_ = false;

			

            Log::Debug("add connection %s \n", session_id_.c_str());
            int ret = request_handler_.start(this);
            if(ret == -1 ){
                Log::Error("request_handler_ start Failed %s",session_id_.c_str());
                this->stop();
				socket_state_ = SOCKETSTATE_FAILED;
                return;
            }
			socket_state_ = SOCKETSTATE_SUCCESS;
            do_read();

        }
        
		
        void dmconnection::stop() {
            
			if (socket_closed_ == false)
			{
				socket_closed_ = true;


				Log::Debug("stop connection %s \n", session_id_.c_str());
				request_handler_.stop();
				socket_.shutdown(boost:: asio::socket_base::shutdown_type::shutdown_both);
				socket_.close();

				

				
			}
          
			socket_state_ = SOCKETSTATE_FAILED;

        }
        
        
        std::string  dmconnection::get_sessionid(){
            return session_id_;
        }
   
        
        void dmconnection::do_read() {
            auto self(shared_from_this());
            
            incoming_buf_.buffer_offset = 0;
            memset(incoming_buf_.buffer, 0, incoming_buf_size_);
            
            int header_len = sizeof(protocol_head_t);
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(incoming_buf_.buffer, header_len),
                                    boost::bind(&dmconnection::handle_msg_length,
									shared_from_this(),
									boost::asio::placeholders::error,
									boost::asio::placeholders::bytes_transferred)
                                    );
            
        }
        
        
        void dmconnection::handle_msg_length(const boost::system::error_code& error,
                                           size_t bytes_transferred)
        {
            auto self(shared_from_this());
            
            if (!error) {
                
                incoming_buf_.buffer_offset = 0;
                incoming_buf_.buffer_len = sizeof(protocol_head_t);
                prot_head_.read(&incoming_buf_);
                
                
                if (prot_head_.nStartFlags == 0xAF && prot_head_.nEndFlags == 0xFA )
                {
                    
                    ensure_incoming_buf_capa(prot_head_.nDataLen);
                    memset(incoming_buf_.buffer, 0, incoming_buf_size_);
                    
                    boost::asio::async_read(socket_,
                                            boost::asio::buffer(incoming_buf_.buffer, prot_head_.nDataLen),
                                            boost::bind(&dmconnection::handle_msg_body,
                                                        shared_from_this(),
                                                        boost::asio::placeholders::error,
                                                        boost::asio::placeholders::bytes_transferred)
                                            );
                    
                }
                else{
                    do_read(); // handle other messages..
                }
                
                
            }
            else if (error != boost::asio::error::operation_aborted) {
				self->stop();
            }
            
        }
        
        void dmconnection::handle_msg_body(const boost::system::error_code& error,
                                         size_t bytes_transferred)
        {
            auto self(shared_from_this());
            if (!error) {
                printf("handle_msg_body len %d result %d \n ", prot_head_.nDataLen, prot_head_.nResult);
                
                //初始化
                incoming_buf_.buffer_offset = 0;
                incoming_buf_.buffer_len = prot_head_.nDataLen;

			//	mutex_buffer_.lock();
                APIProtocal_Handler(prot_head_,&incoming_buf_,&request_handler_);
				//mutex_buffer_.unlock();

                do_read();               
        
            }
            else if (error != boost::asio::error::operation_aborted) {
				self->stop();

            }
        }
        
        
        
        
        void  dmconnection::ensure_incoming_buf_capa(size_t required_size)
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
        
	
        
        void dmconnection::do_write(response& res) {
			if (this == NULL)
			{
				return;
			}
// 			std::shared_ptr<dmconnection> self = shared_from_this();
// 			if (!self)
// 			{
// 				return;
// 			}
			auto self(shared_from_this());
            std::vector<boost::asio::const_buffer> buffer = res.to_buffers();
				boost::asio::async_write(
					socket_, buffer,
					[this, self](boost::system::error_code ec, std::size_t n) {
					if (!ec) {
						Log::Debug(">>>>  boost::asio::async_write  %d", n);
					}
					else if (ec != boost::asio::error::operation_aborted) {

						Log::Error("boost::asio::async_write start  size_t %d", n);
						Log::Error("boost::asio::async_write start  error_code  code %d msg %s", ec.value(), ec.message().c_str());

						self->stop();
					}
				});
        }
        
        
        
        
        
    }  // namespace server
}  // namespace dem1


