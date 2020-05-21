#ifndef IOTWGT_H
#define IOTWGT_H

#include <QWidget>
#include <QWebEngineView>
#include "ui_iotwgt.h"

class IOTWgt : public QWidget
{
	Q_OBJECT

public:
	explicit IOTWgt(QWidget *parent = 0);
	~IOTWgt();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	QWebEngineView *m_platform_view;
private:
	Ui::IOTWgt ui;
};

#endif // IOTWGT_H
