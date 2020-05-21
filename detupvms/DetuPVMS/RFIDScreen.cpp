#include <QGraphicsOpacityEffect>

#include "RFIDScreen.h"

#include "RFIDDataManager.h"


RFIDScreen::RFIDScreen(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.pushButton1, SIGNAL(clicked()), this, SLOT(OnPushButton1ClickedSlot()));
	connect(ui.pushButton2, SIGNAL(clicked()), this, SLOT(OnPushButton2ClickedSlot()));
	connect(ui.pushButton3, SIGNAL(clicked()), this, SLOT(OnPushButton3ClickedSlot()));
	connect(ui.pushButton4, SIGNAL(clicked()), this, SLOT(OnPushButton4ClickedSlot()));

	connect(&RFIDDataManagerIns, SIGNAL(SignalToUi(int, int)), this, SLOT(slotOnShowRFID(int, int)));

	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;

	this->setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.7);

}

RFIDScreen::~RFIDScreen()
{

}

void RFIDScreen::OnPushButton1ClickedSlot()
{
	emit SignalToSetSwtichScreen(1);
}

void RFIDScreen::OnPushButton2ClickedSlot()
{
	emit SignalToSetSwtichScreen(2);
}

void RFIDScreen::OnPushButton3ClickedSlot()
{
	emit SignalToSetSwtichScreen(3);
}

void RFIDScreen::OnPushButton4ClickedSlot()
{
	emit SignalToSetSwtichScreen(4);
}

void RFIDScreen::slotOnShowRFID(int type, int equip_id)
{

	//��ʾ
	switch (type)
	{

	case 128:		//�Ž�����
	{
						switch (equip_id)
						{
						case 0: //װ����ȫ						
						{
									break;
						}
						case 1:	//ȱ��ͷ��
						{
									ui.text_label->setText(QStringLiteral("��⵽װ������ȫ��ȱ��ͷ��"));
									break;
						}
						case 2:	//ȱ���·�
						{
									ui.text_label->setText(QStringLiteral("��⵽װ������ȫ��ȱ���·�"));
									break;
						}
						case 3:	//ȱ������
						{
									ui.text_label->setText(QStringLiteral("��⵽װ������ȫ��ȱ������"));
									break;
						}
						case 4:	//����
						{
									ui.text_label->setText(QStringLiteral("��⵽װ����ȫ������"));
									break;
						}
						case 5:	//����
						{
									ui.text_label->setText(QStringLiteral("��⵽װ����ȫ������"));
									break;
						}
						case 6:	//û������ѵ
						{
									ui.text_label->setText(QStringLiteral("��⵽δ������ѵ"));
									break;
						}
						default:
							break;
						}
						break;
	}
	case 129:		//Σ������
	{				
						QString id = QString::number(equip_id);
						ui.text_label_2->setText(QStringLiteral("��⵽���ֱ���",id));
						break;
	}
	case 130:		//Ȩ������
	{
				switch (equip_id)
				{
				case 0:				
				{
						  ui.text_label_3->setText(QStringLiteral("��⵽��Ȩ��Ա��������"));
						  break;
				}
				case 1:
				{
						  ui.text_label_3->setText(QStringLiteral("��⵽��Ȩ��Ա��������"));
						  break;
				}
				default:
					break;
				}
				break;
	}

	case 200:		//��ʾ������
	{						  
						switch (equip_id)
						{
						case 0: 
						{
							ui.text_label_4->setText(QStringLiteral("��⵽�������쳣"));
							break;
						}
						case 1:
						{
							ui.text_label_4->setText(QStringLiteral("��⵽����˨�쳣"));
							break;
						}
						case 2:
						{
							ui.text_label_4->setText(QStringLiteral("��⵽��Դ���쳣"));
							break;
						}
						case 100:
						{
									ui.text_label_4->setText(QStringLiteral(""));
									break;
						}
						default:
							break;
						}
						break;
	}
	default:
		break;
	}

}