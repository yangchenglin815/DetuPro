#include "showBandWidthDlg.h"

showBandWidthDlg::showBandWidthDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	ui.closeBtn->setVisible(false);
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(close()));
}

showBandWidthDlg::~showBandWidthDlg()
{

}

void showBandWidthDlg::setBandWidth(QString pvsID, int bandWidth1, int bandWidth2)
{
	ui.deviceLabel->setText(pvsID);
	ui.bandWidthLabel1->setText(QString::number(bandWidth1) + "   Byte/s");
	ui.bandWidthLabel2->setText(QString::number(bandWidth2) + "   Byte/s");
}
