#ifndef COMMONTIPDLG_H
#define COMMONTIPDLG_H

#include <QDialog>
#include "ui_commonTipDlg.h"

class commonTipDlg : public QDialog
{
	Q_OBJECT

public:
	commonTipDlg(QWidget *parent = 0);
	~commonTipDlg();
	void setTitleLabelText(QString titleText);
	void setTipText(QString tipText);
signals:
	void sigOnConfirm();
private:
	void initConnect();
private:
	Ui::commonTipDlg ui;
};

#endif // COMMONTIPDLG_H
