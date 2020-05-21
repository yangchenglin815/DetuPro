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

// ʹ�ú��������ʵ��
#define DetuNvrlist detuNvrList::GetInstance()

namespace dem1 {
    namespace server {

        class connection;

        class detuNvrList
        {

        private:
            friend class auto_ptr<detuNvrList>;				/// ʹ������ָ��
            /// ��ʹ��δ������Ҳ�ᱻ����(����);�������ʹ��static ���Σ���˼��ֻ��һ������ᱻ����������
            /// ���캯������Ϊ private �����Է�ֹ����Ĳ�����(auto_ptr need #include <memory>)
            static auto_ptr<detuNvrList> auto_ptr_instance;	/// Ωһʵ��

        private:
            detuNvrList();	/// ���캯��(ע��:���췽��˽��)
            ~detuNvrList(void);							/// ��������

        public:
            static detuNvrList& GetInstance(void);		/// ʵ��(��������)

			//�߼�����
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

			//��Ƶ����
			void updateCurrentNvrRtmpPath(std::string session_id, std::string nvr_rtmp_path);
			std::string getRtmpPathByDeivceId(std::string session_id);

			void addNvrPts(protocol_head_t *head, netbuffer *buf);
        private:

			std::map<std::string, api_detu_client_register_res_t >  nvr_list_;			//����session_id��nvr�б�
			std::map<std::string, std::string >  nvr_current_rtmp_path_;	//����nvr session_id�͵�ǰ���������ַ
			std::map<std::string, api_pts_file > pts_list_;

			std::vector<api_record_query_t>nvr_keep_five_pts_list_;
        };

    }
}