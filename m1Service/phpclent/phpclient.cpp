#include "phpclient.h"

using namespace std;


		auto_ptr<phpclient> phpclient::auto_ptr_instance;
		phpclient::phpclient()
		{
		}


		phpclient::~phpclient()
		{
		}


		phpclient& phpclient::GetInstance(void)
		{
			if (auto_ptr_instance.get() == 0) {
				auto_ptr_instance.reset(new phpclient());
			}
			return *(auto_ptr_instance.get());
		}

		int phpclient::callback(void *NotUsed, int argc, char **argv, char **azColName)
		{
			int i;
			for (i = 0; i < argc; i++){
				if (argv[i] != NULL)
				{
					phpclientIns.m_result.push_back(std::string(argv[i]));
				}
				else
				{
					phpclientIns.m_result.push_back("");
				}
			}
			return 0;
		}

