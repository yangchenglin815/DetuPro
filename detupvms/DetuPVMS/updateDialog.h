#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include "ui_updateDialog.h"

class updateDialog : public QDialog
{
	Q_OBJECT

public:
	updateDialog(QWidget *parent = 0);
	~updateDialog();
private:
	Ui::updateDialog ui;
};

#endif // UPDATEDIALOG_H
