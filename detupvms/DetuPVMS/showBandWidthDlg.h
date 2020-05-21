#ifndef SHOWBANDWIDTHDLG_H
#define SHOWBANDWIDTHDLG_H

#include <QDialog>
#include "ui_showBandWidthDlg.h"

class showBandWidthDlg : public QDialog
{
	Q_OBJECT

public:
	showBandWidthDlg(QWidget *parent = 0);
	~showBandWidthDlg();
	void setBandWidth(QString pvsID, int bandWidth1, int bandWidth2);
private:
	Ui::showBandWidthDlg ui;
};

#endif // SHOWBANDWIDTHDLG_H
