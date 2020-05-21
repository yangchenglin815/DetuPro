#ifndef DISKFORMATDLG_H
#define DISKFORMATDLG_H

#include <QDialog>
#include "ui_diskFormatDlg.h"

class diskFormatDlg : public QDialog
{
	Q_OBJECT

public:
	diskFormatDlg(QWidget *parent = 0);
	~diskFormatDlg();
signals:
	void sigOnDiskFormat();
private:
	void initConnect();
	void init();
private:
	Ui::diskFormatDlg ui;
};

#endif // DISKFORMATDLG_H
