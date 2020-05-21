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

	//提示
	switch (type)
	{

	case 128:		//门禁区域
	{
						switch (equip_id)
						{
						case 0: //装备齐全						
						{
									break;
						}
						case 1:	//缺少头盔
						{
									ui.text_label->setText(QStringLiteral("检测到装备不齐全，缺少头盔"));
									break;
						}
						case 2:	//缺少衣服
						{
									ui.text_label->setText(QStringLiteral("检测到装备不齐全，缺少衣服"));
									break;
						}
						case 3:	//缺少手套
						{
									ui.text_label->setText(QStringLiteral("检测到装备不齐全，缺少手套"));
									break;
						}
						case 4:	//进门
						{
									ui.text_label->setText(QStringLiteral("检测到装备齐全，进门"));
									break;
						}
						case 5:	//出门
						{
									ui.text_label->setText(QStringLiteral("检测到装备齐全，出门"));
									break;
						}
						case 6:	//没经过培训
						{
									ui.text_label->setText(QStringLiteral("检测到未经过培训"));
									break;
						}
						default:
							break;
						}
						break;
	}
	case 129:		//危险区域
	{				
						QString id = QString::number(equip_id);
						ui.text_label_2->setText(QStringLiteral("检测到入侵报警",id));
						break;
	}
	case 130:		//权限区域
	{
				switch (equip_id)
				{
				case 0:				
				{
						  ui.text_label_3->setText(QStringLiteral("检测到有权限员工，正常"));
						  break;
				}
				case 1:
				{
						  ui.text_label_3->setText(QStringLiteral("检测到无权限员工，入侵"));
						  break;
				}
				default:
					break;
				}
				break;
	}

	case 200:		//警示牌区域
	{						  
						switch (equip_id)
						{
						case 0: 
						{
							ui.text_label_4->setText(QStringLiteral("检测到警告牌异常"));
							break;
						}
						case 1:
						{
							ui.text_label_4->setText(QStringLiteral("检测到消防栓异常"));
							break;
						}
						case 2:
						{
							ui.text_label_4->setText(QStringLiteral("检测到电源柜异常"));
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