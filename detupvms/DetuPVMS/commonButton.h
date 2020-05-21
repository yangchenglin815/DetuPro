#ifndef COMMONBUTTON_H
#define COMMONBUTTON_H

#include <QPushButton>
#include "ui_commonButton.h"

class commonButton : public QPushButton
{
	Q_OBJECT

public:
	commonButton(QWidget *parent = 0);
	~commonButton();
	void initStyleSheet(QString style, QString hover_style);
	void setButtonName(QString name);
	void setButtonSize(int width, int height);
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	QString m_common_style;
	QString m_hover_style;
private:
	Ui::commonButton ui;
};

#endif // COMMONBUTTON_H
