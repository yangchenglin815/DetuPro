#include "qrCodeDlg.h"
#include "logging.hpp"

qrCodeDlg::qrCodeDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	initConnect();
}

qrCodeDlg::~qrCodeDlg()
{

}

void qrCodeDlg::initConnect()
{
	connect(ui.closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void qrCodeDlg::initData(QString pvsID, QString IP, QString port)
{
	QString qrCode = QString("http://%1:%2/%3").arg(IP).arg(port).arg(pvsID);
	ui.qrGenerateWidget->generateString(qrCode);
	Log::Info("QRCode : %s", qrCode.toLocal8Bit().data());
}
