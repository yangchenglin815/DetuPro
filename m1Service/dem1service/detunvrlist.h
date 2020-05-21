#pragma once

#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <memory>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include <list>
#include "core.h"

#include "APIProtocol.h"

using namespace std;

// 使用宏替代单例实例
#define DetuNvrlist detuNvrList::GetInstance()

namespace dem1 {
    namespace server {

        class connection;

        class detuNvrList
        {

        private:
            friend class auto_ptr<detuNvrList>;				/// 使用智能指针
            /// 即使从未被调用也会被构造(析构);如果对象使用static 修饰，意思是只有一个对象会被产生出来。
            /// 构造函数属性为 private ，可以防止对象的产生。(auto_ptr need #include <memory>)
            static auto_ptr<detuNvrList> auto_ptr_instance;	/// 惟一实例

        private:
            detuNvrList();	/// 构造函数(注意:构造方法私有)
            ~detuNvrList(void);							/// 析构函数

        public:
            static detuNvrList& GetInstance(void);		/// 实例(工厂方法)

			//逻辑控制
            bool isDeviceIdExist(std::string deviceId);

			void addSessionId(std::string session_id, api_detu_client_register_res_t api_reg);
			void addSessionId(std::string session_id, unsigned char* m1DeviceId, int nPtsLen, unsigned char* ptsData);

			void saveDeviceName(std::string session_id, api_detu_client_register_res_t api_reg);
			void savePTSData(std::string session_id, api_detu_client_optmize_t api_reg);
			bool savePTZ(api_detu_client_register_res_t api_reg);
            void removeSessionId(std::string session_id);
            std::string getSessionIdByDeivceId(std::string deviceId);
			std::string getDeviceIdBySessionld(std::string sessionid);
			std::map < std::string, api_detu_client_register_res_t> getNvrList();
			std::map< std::string, api_pts_file_t> getPtsList();

			//视频控制
			void updateCurrentNvrRtmpPath(std::string session_id, std::string nvr_rtmp_path);
			std::string getRtmpPathByDeivceId(std::string session_id);

			void addNvrPts(protocol_head_t *head, netbuffer *buf);
        private:

			std::map<std::string, api_detu_client_register_res_t >  nvr_list_;			//保存session_id和nvr列表
			std::map<std::string, std::string >  nvr_current_rtmp_path_;	//保存nvr session_id和当前请求的流地址
			std::map<std::string, api_pts_file > pts_list_;

			std::vector<api_record_query_t>nvr_keep_five_pts_list_;
        };

    }
}