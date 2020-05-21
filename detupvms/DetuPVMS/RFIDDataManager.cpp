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
				//先判断有没有进入
				if (online_data_list_[insert_id - 1].is_in)
				{
					online_data_list_[insert_id - 1].end_time = QTime::currentTime();

					//如果已经进入并且不超过10分钟，啥都不干
					if ((online_data_list_[insert_id - 1].end_time.minute()
						- online_data_list_[insert_id - 1].start_time.minute())<10)
					{
						return;
					}
					//超过十分钟，清空数据开门
					else
					{
						//需要记录工时，出入情况







						online_data_list_[insert_id - 1].clear();

						//发信号通知开门出
						emit SignalToOpenDoor(0);
						emit SignalToUi(type, 5);
					}
				}
				else
				{
					//没有进入
					//往在线列表塞数据
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
					*判断当前设备对应的人员是否齐全，
					*如果齐全，
					*判断是否已经进入
					*已进入，不做处理
						*没进入，
							*如果通过培训，开门，切换标志位
							*如果没通过培训，通知且不开门
					*如果不齐全，不做处理，甚至报警
					*/
					if (online_data_list_[insert_id - 1].IsPackaged())
					{
						if (!online_data_list_[insert_id - 1].is_in)
						{
							if (is_trained == "0000")
							{
								online_data_list_[insert_id - 1].is_in = true;
								online_data_list_[insert_id - 1].start_time = QTime::currentTime();
								//发信号通知开门入
								emit SignalToOpenDoor(1);
								emit SignalToUi(type, 4);
							}
							else

							{
								emit SignalToUi(type, 6);
							}

						}
					}
					else  //不齐全，可以通知UI
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
				//先判断有没有进入
				if (!online_data_list_[insert_id - 1].is_in)
				{
					return;
				}
				else
				{
					//危险区域，任何时候到报警
					emit SignalToUi(type, insert_id);
				}
				break;
	}
	case 130:
	{
				//先判断有没有进入
				if (!online_data_list_[insert_id - 1].is_in)
				{
					return;
				}
				else
				{
					if (is_limited=="0001")
					{					
						//危险区域，任何时候到报警
						emit SignalToUi(type, 1);
					}
					else
					{
						//记录
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

