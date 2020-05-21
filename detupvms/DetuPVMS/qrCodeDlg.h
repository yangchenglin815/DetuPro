#ifndef QRCODEDLG_H
#define QRCODEDLG_H

#include <QDialog>
#include "ui_qrCodeDlg.h"

class qrCodeDlg : public QDialog
{
	Q_OBJECT

public:
	qrCodeDlg(QWidget *parent = 0);
	~qrCodeDlg();
	void initData(QString pvsID, QString IP, QString port);
private:
	void initConnect();
private:
	Ui::qrCodeDlg ui;
};

#endif // QRCODEDLG_H
