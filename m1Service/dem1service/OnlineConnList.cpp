#include "OnlineConnList.h"

namespace dem1 {
	namespace server {
		/// ��������
		/// ���� class static ������class ֮������������Ҫ��class ֮�ⶨ��.
		auto_ptr<OnlineConnList> OnlineConnList::auto_ptr_instance;

		OnlineConnList::OnlineConnList()
		{
			online_conn_.clear();
			online_conn_.resize(0);
		}


		OnlineConnList::~OnlineConnList()
		{
		}

		OnlineConnList& OnlineConnList::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new OnlineConnList());
			}
			return *(auto_ptr_instance.get());
		}




		void OnlineConnList::AddOnlineConn(OnlineConnInfo_t conn)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl_);
			online_conn_.push_back(conn);
		}



		std::vector<string> OnlineConnList::GetList(OnlineConnInfo_t conn)
		{
			boost::lock_guard<boost::mutex> lock(mutex_ctrl_);
			std::vector<string>session;

			vector<OnlineConnInfo_t>::iterator iterator;


			for (iterator = online_conn_.begin(); iterator != online_conn_.end();)
			{
				if ((*iterator )== conn)
				{
					session.push_back(iterator->client_session);
					//��ѯ�����������ɾ��
					online_conn_.erase(iterator);
				}
				else
				{
					++iterator;
				}
			}

			return session;

		}

	}
}