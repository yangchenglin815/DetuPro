#include "addDeviceDlg.h"
#include "constStruct.h"
#include "selectedItemWidget.h"

addDeviceDlg::addDeviceDlg(QWidget *parent)
	: QDialog(parent)
	, m_ctrlGroup(NULL)
	, m_currType(-1)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint);
	init();
	initConnect();
}

addDeviceDlg::~addDeviceDlg()
{

}

/*************************************************
函数名:    	setTitleLabel
函数描述:	设置标题栏label
输入参数:    text ： 文本
输出参数:
返回值:
**************************************************/
void addDeviceDlg::setTitleLabel(QString text)
{
	ui.titleLabel->setText(text);
}


/*************************************************
函数名:    	clearData
函数描述:	清空编辑区域数据
输入参数:
输出参数:
返回值:
**************************************************/
void addDeviceDlg::clearData()
{
	ui.ipLineEdit->setText("");
	ui.portLineEdit->setText("");
	ui.userLineEdit->setText("");
	ui.passwdLineEdit->setText("");
	ui.hintLabel->setText("");
}

void addDeviceDlg::setType(int type)
{
	m_currType = type;
}

void addDeviceDlg::initPTZList(const QList<PtzInfo> &ptzInfoList)
{
	m_ptzInfoList = ptzInfoList;
}

void addDeviceDlg::initSPYList(const QList<SpyInfo> &spyInfoList)
{
	m_spyInfoList = spyInfoList;
}

void addDeviceDlg::setData(QString IP, int port, QString username, QString passwd)
{
	ui.ipLineEdit->setText(IP);
	ui.portLineEdit->setText(QString::number(port));
	ui.userLineEdit->setText(username);
	ui.passwdLineEdit->setText(passwd);
}

void addDeviceDlg::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter){
		slotOnConfirm();
	}
}

/*************************************************
函数名:    	slotOnConfirm
函数描述:	确认按钮触发槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void addDeviceDlg::slotOnConfirm()
{
	if (ui.stackedWidget->currentIndex() == 0)
	{
		ui.hintLabel->setText("");
		if (ui.ipLineEdit->text().isEmpty()){
			ui.ipLineEdit->setFocus();
			ui.hintLabel->setText(QStringLiteral("IP地址不能为空"));
			return;
		}
		else if (ui.portLineEdit->text().isEmpty())
		{
			ui.portLineEdit->setFocus();
			ui.hintLabel->setText(QStringLiteral("端口不能为空"));
			return;
		}
		else if (ui.userLineEdit->text().isEmpty())
		{
			ui.userLineEdit->setFocus();
			ui.hintLabel->setText(QStringLiteral("用户名不能为空"));
			return;
		}
		else if (ui.passwdLineEdit->text().isEmpty())
		{
			ui.passwdLineEdit->setFocus();
			ui.hintLabel->setText(QStringLiteral("密码不能为空"));
			return;
		}
		else
		{
			ui.hintLabel->setText("");
			QString IP = ui.ipLineEdit->text();
			int port = ui.portLineEdit->text().toInt();
			QString userName = ui.userLineEdit->text();
			QString passwd = ui.passwdLineEdit->text();
			emit sigOnBindPtz(IP, port, userName, passwd, m_currType);
			this->close();
		}
	}
	else
	{
		switch (m_currType)
		{
		case 0:
			emit sigOnBindPtz(m_curr_ptzInfo.sIP, m_curr_ptzInfo.wPort, m_curr_ptzInfo.sUserName, m_curr_ptzInfo.sPasswd, m_currType);
			break;
		case 1:
			emit sigOnBindPtz(m_curr_SpyInfo.sIP, m_curr_SpyInfo.wPort, m_curr_SpyInfo.sUserName, m_curr_SpyInfo.sPasswd, m_currType);
			break;
		default:
			break;
		}		
	}
}

/*************************************************
函数名:    	slotOnPageChanged
函数描述:	选项卡按钮触发槽函数
输入参数:
输出参数:
返回值:
**************************************************/
void addDeviceDlg::slotOnPageChanged(int index)
{
	switch (index)
	{
	case 0:
		ui.stackedWidget->setCurrentIndex(index);
		break;
	case 1:
		ui.stackedWidget->setCurrentIndex(index);
		initListData();
		break;
	}
}

void addDeviceDlg::slotOnItemClicked(QListWidgetItem *item, QListWidgetItem *previousItem)
{
	selectedItemWidget *itemWidget = qobject_cast<selectedItemWidget*>(ui.listWidget->itemWidget(item));
	if (itemWidget)
	{
		itemWidget->setChecked();
		itemWidget->getPTZData(m_curr_ptzInfo);
		itemWidget->getSPYData(m_curr_SpyInfo);
	}
	selectedItemWidget *previousItemWidget = qobject_cast<selectedItemWidget*>(ui.listWidget->itemWidget(previousItem));
	if (previousItemWidget)
	{
		previousItemWidget->setChecked();
	}
}

void addDeviceDlg::init()
{
	ui.addDeviceBtn->setChecked(true);
	ui.stackedWidget->setCurrentWidget(ui.addDevicePage);
	ui.userLineEdit->setMaxLength(30);
	ui.passwdLineEdit->setMaxLength(20);
	QRegExp regx("[a-zA-Z0-9]*");
	QRegExpValidator *validator = new QRegExpValidator(regx, this);
	ui.userLineEdit->setValidator(validator);
	ui.passwdLineEdit->setValidator(validator);
	ui.passwdLineEdit->setEchoMode(QLineEdit::Password);
	QRegExp regx_("[1-9][0-9]+$");
	QValidator *validator_ = new QRegExpValidator(regx_, this);
	ui.portLineEdit->setValidator(validator_);
	ui.portLineEdit->setMaxLength(5);
	m_ctrlGroup = new QButtonGroup(this);
	m_ctrlGroup->addButton(ui.addDeviceBtn, 0);
	m_ctrlGroup->addButton(ui.selectedBtn, 1);
	ui.listWidget->setFocusPolicy(Qt::NoFocus);
}

void addDeviceDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(slotOnConfirm()));
	connect(m_ctrlGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotOnPageChanged(int)));
	connect(ui.listWidget, SIGNAL(currentItemChanged(QListWidgetItem*, QListWidgetItem*)), this, SLOT(slotOnItemClicked(QListWidgetItem*, QListWidgetItem*)));
}

void addDeviceDlg::initListData()
{
	switch (m_currType)
	{
	case 0:
		ui.listWidget->clear();
		for (int i = 0; i < m_ptzInfoList.size(); ++i)
		{
			selectedItemWidget *itemWidget = new selectedItemWidget;
			itemWidget->initPTZData(m_ptzInfoList[i]);
			QListWidgetItem *item = new QListWidgetItem;
			item->setSizeHint(QSize(200, 30));
			ui.listWidget->insertItem(i, item);
			ui.listWidget->setItemWidget(item, itemWidget);
		}
		break;
	case 1:
		ui.listWidget->clear();
		for (int i = 0; i < m_spyInfoList.size(); ++i)
		{
			selectedItemWidget *itemWidget = new selectedItemWidget;
			itemWidget->initSPYData(m_spyInfoList[i]);
			QListWidgetItem *item = new QListWidgetItem;
			item->setSizeHint(QSize(200, 30));
			ui.listWidget->insertItem(i, item);
			ui.listWidget->setItemWidget(item, itemWidget);
		}
		break;
	default:
		break;
	}
}
