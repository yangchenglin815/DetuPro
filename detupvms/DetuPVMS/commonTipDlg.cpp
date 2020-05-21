#include "commonTipDlg.h"

commonTipDlg::commonTipDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	initConnect();
}

commonTipDlg::~commonTipDlg()
{

}

void commonTipDlg::setTitleLabelText(QString titleText)
{
	ui.titleLabel->setText(titleText);
}

void commonTipDlg::setTipText(QString tipText)
{
	ui.tipLabel->setText(tipText);
}

void commonTipDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SIGNAL(sigOnConfirm()));
}
