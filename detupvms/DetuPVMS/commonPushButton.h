#ifndef COMMONPUSHBUTTON_H
#define COMMONPUSHBUTTON_H

#include <QPushButton>

class commonPushButton : public QPushButton
{
	Q_OBJECT
public:
	explicit commonPushButton(QWidget *parent = 0);
	~commonPushButton();
protected:
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
};

#endif // COMMONPUSHBUTTON_H
