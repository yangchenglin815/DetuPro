#ifndef GUNCAMMINIITEM_H
#define GUNCAMMINIITEM_H

#include <QWidget>
#include "ui_gunCamMiniItem.h"

class gunCamMiniItem : public QWidget
{
	Q_OBJECT

public:
	gunCamMiniItem(QWidget *parent = 0);
	~gunCamMiniItem();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

signals:
	//设置热点图片地址
	void SignalToSetHotPicPath(QString hot_pic_path);

public:
	QString getHotPicPath(){ return hotpic_; };
private:
	Ui::gunCamMiniItem ui;

	bool is_hot_pic_chosen_;
	QString hotpic_;
};

#endif // GUNCAMMINIITEM_H
