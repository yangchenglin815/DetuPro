#ifndef COMMONCOMBOX_H
#define COMMONCOMBOX_H

#include <QComboBox>

class commonComBox : public QComboBox
{
	Q_OBJECT
public:
	explicit commonComBox(QWidget *parent = 0);
	~commonComBox();
protected:
	void wheelEvent(QWheelEvent *e);
};

#endif // COMMONCOMBOX_H
