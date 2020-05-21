#include "RFIDDataManager.h"


RFIDDataManager::RFIDDataManager()
{
	data_base_list_.resize(6);
	data_base_list_[0].Init("0001", "0001", "0002", "0003");
	data_base_list_[1].Init("0002", "0001", "0002", "0003");
	data_base_list_[2].Init("0003", "0001", "0002", "0003");
	data_base_list_[3].Init("0004", "0001", "0002", "0003");
	data_base_list_[4].Init("0005", "0001", "0002", "0003");
	data_base_list_[5].Init("0006", "0001", "0002", "0003");

	online_data_list_.resize(6);
}


void RFIDDataManager::AddId(QString id, int type)
{
	int insert_id = id.left(4).toInt();
	QString is_trained = id.left(8).right(4);
	QString is_limited = id.right(8).left(4);

	if (insert_id < 1 || insert_id>5)
	{
		return;
	}

	int insert_equipment_id = id.right(4).toInt();

	switch (type)
	{
	case 128:
	{
				//���ж���û�н���
				if (online_data_list_[insert_id - 1].is_in)
				{
					online_data_list_[insert_id - 1].end_time = QTime::currentTime();

					//����Ѿ����벢�Ҳ�����10���ӣ�ɶ������
					if ((online_data_list_[insert_id - 1].end_time.minute()
						- online_data_list_[insert_id - 1].start_time.minute())<10)
					{
						return;
					}
					//����ʮ���ӣ�������ݿ���
					else
					{
						//��Ҫ��¼��ʱ���������







						online_data_list_[insert_id - 1].clear();

						//���ź�֪ͨ���ų�
						emit SignalToOpenDoor(0);
						emit SignalToUi(type, 5);
					}
				}
				else
				{
					//û�н���
					//�������б�������
					switch (insert_equipment_id)
					{
					case 1:
					{
		
							  online_data_list_[insert_id - 1].helmet_id = "0001";
							  break;
					}
					case 2:
					{

							  online_data_list_[insert_id - 1].cloth_id = "0002";
							  break;
					}
					case 3:
					{
							  online_data_list_[insert_id - 1].glove_id = "0003";
							  break;
					}
					default:
						break;
					}

					/*
					*�жϵ�ǰ�豸��Ӧ����Ա�Ƿ���ȫ��
					*�����ȫ��
					*�ж��Ƿ��Ѿ�����
					*�ѽ��룬��������
						*û���룬
							*���ͨ����ѵ�����ţ��л���־λ
							*���ûͨ����ѵ��֪ͨ�Ҳ�����
					*�������ȫ������������������
					*/
					if (online_data_list_[insert_id - 1].IsPackaged())
					{
						if (!online_data_list_[insert_id - 1].is_in)
						{
							if (is_trained == "0000")
							{
								online_data_list_[insert_id - 1].is_in = true;
								online_data_list_[insert_id - 1].start_time = QTime::currentTime();
								//���ź�֪ͨ������
								emit SignalToOpenDoor(1);
								emit SignalToUi(type, 4);
							}
							else

							{
								emit SignalToUi(type, 6);
							}

						}
					}
					else  //����ȫ������֪ͨUI
					{
						if (online_data_list_[insert_id - 1].helmet_id == "null")
						{
							emit SignalToUi(type, 1);
							return;
						}
						if (online_data_list_[insert_id - 1].cloth_id == "null")
						{
							emit SignalToUi(type, 2);
							return;
						}
						if (online_data_list_[insert_id - 1].glove_id == "null")
						{
							emit SignalToUi(type, 3);
							return;
						}

					}
				}
				break;
	}
	case 129:
	{
				//���ж���û�н���
				if (!online_data_list_[insert_id - 1].is_in)
				{
					return;
				}
				else
				{
					//Σ�������κ�ʱ�򵽱���
					emit SignalToUi(type, insert_id);
				}
				break;
	}
	case 130:
	{
				//���ж���û�н���
				if (!online_data_list_[insert_id - 1].is_in)
				{
					return;
				}
				else
				{
					if (is_limited=="0001")
					{					
						//Σ�������κ�ʱ�򵽱���
						emit SignalToUi(type, 1);
					}
					else
					{
						//��¼
						emit SignalToUi(type, 0);
					}

				}
				break;
				break;

	}
	default:
		break;
	}			
}

