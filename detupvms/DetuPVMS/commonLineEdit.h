/************************************************
* \file commonLineEdit.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 登录弹框中定制的LineEdit
************************************************/
#ifndef COMMONLINEEDIT_H
#define COMMONLINEEDIT_H

#include <QWidget>
#include "ui_commonLineEdit.h"

class commonLineEdit : public QWidget
{
	Q_OBJECT

public:
	commonLineEdit(QWidget *parent = 0);
	~commonLineEdit();
	void setHintText(QString str);
	void setMaxLength(int num);
	void setValidator(QRegExpValidator* validator);
	void setText(QString str);
	void setFocusLineEdit();
	void setShowClose(bool isHidden);
	QString getText();
private slots:
void slot_clearText();
private:
	void initConnect();
private:
	Ui::commonLineEdit ui;
};

#endif // COMMONLINEEDIT_H
