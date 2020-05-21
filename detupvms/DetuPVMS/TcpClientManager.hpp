#ifndef RTSP_CLIENT_HPP
#define RTSP_CLIENT_HPP

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <map>
#include <QObject>
#include <memory>

#include "APIProtocol.h"
#include "UiSingleton.h"
#include "logging.h"

#define  TcpManager dem1::client::TcpClientManager
#define  TcpManagerIns dem1::client::TcpClientManager::Instance()

class DetuPVMS;

using namespace dem1::server;

namespace dem1 {
	namespace client {
		struct response {
			std::string status_line;
			std::map<std::string, std::string> headers;
			std::string content;
		};

		class TcpClientManager :public QObject, public CUiSingleton<TcpClientManager>
        {
            Q_OBJECT
			friend class CUiSingleton<TcpClientManager>;
		private:
			TcpClientManager();

		public:
			//TcpClientManager(const TcpClientManager&) = delete;             // not copiable
			//TcpClientManager& operator=(const TcpClientManager&) = delete;  // not copiable
			//TcpClientManager(const std::string& address, uint16_t port);

			void init(const std::string& address, uint16_t port);


            void sendData(protocol_head_t api_head, api_register_t api_reg);
            void sendData(protocol_head_t api_head, api_detu_client_request_video_t api_detu);

			void do_read();

            api_register_res_list_t* GetList(){ return &api_reg_res_; };

			void SetMainWindow(DetuPVMS* main_window);

			void close();
		signals:
			void DetuClientLoginOk();
			void DetuClientLoginFailed();
            void NvrListReceived();

		private:


			void handle_msg_length(const boost::system::error_code& error, size_t bytes_transferred);
			void handle_msg_body(const boost::system::error_code& error, size_t bytes_transferred);

			void ensure_incoming_buf_capa(size_t required_size);

		private:

			boost::asio::io_service io_service_;
			boost::asio::ip::tcp::socket socket_{ io_service_ };
			std::string address_;
			uint16_t port_;
			std::string session_;
			std::string url_;
	
			boost::mutex do_read_mutx_;

			/// Buffer for incoming data.
			protocol_head_t prot_head_;
			int incoming_buf_size_;
			netbuffer_t incoming_buf_;

            api_register_res_list_t  api_reg_res_;

			DetuPVMS *mainwindow_;

			bool is_tcp_closed_;
		};

	}  // namespace client
}


#endif 
