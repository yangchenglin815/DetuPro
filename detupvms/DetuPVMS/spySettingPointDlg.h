#ifndef SPYSETTINGPOINTDLG_H
#define SPYSETTINGPOINTDLG_H

#include <QDialog>
#include "ui_spySettingPointDlg.h"

class spySettingPointDlg : public QDialog
{
	Q_OBJECT

public:
	spySettingPointDlg(QWidget *parent = 0);
	~spySettingPointDlg();

private:
	Ui::spySettingPointDlg ui;
};

#endif // SPYSETTINGPOINTDLG_H
