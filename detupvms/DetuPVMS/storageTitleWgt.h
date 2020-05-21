#ifndef STORAGETITLEWGT_H
#define STORAGETITLEWGT_H

#include <QWidget>

class storageTitleWgt : public QWidget
{
	Q_OBJECT

public:
	explicit storageTitleWgt(QWidget *parent = 0);
	~storageTitleWgt();
protected:
	void paintEvent(QPaintEvent *event);
};

#endif // STORAGETITLEWGT_H
