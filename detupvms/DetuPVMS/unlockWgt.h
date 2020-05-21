#ifndef UNLOCKWGT_H
#define UNLOCKWGT_H

#include <QWidget>
#include <QKeyEvent>
#include "ui_unlockWgt.h"

class unlockWgt : public QWidget
{
	Q_OBJECT

public:
	unlockWgt(QWidget *parent = 0);
	~unlockWgt();
	void clearPasswd();
	void setBtnState();
	void getUserName();
signals:
	void sigOnClose();
	void sigOnUnlock();
	void sigOnModel(bool model);
private slots:
    void slot_unlock();
protected:
	void keyPressEvent(QKeyEvent *event);
	bool eventFilter(QObject *watched, QEvent *event);
private:
	void init();
	void initConnect();
private:
	Ui::unlockWgt ui;
};

#endif // UNLOCKWGT_H
