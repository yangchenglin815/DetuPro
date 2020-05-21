#ifndef COMMONLISTWIDGET_H
#define COMMONLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>

#include "constStruct.h"
class commonListWidget : public QListWidget
{
	Q_OBJECT

public:
	explicit commonListWidget(QWidget *parent = 0);
	~commonListWidget();
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

signals:
	void sigOnAddMapPoint(/*PanoSceneInfo pano_scene_info*/);

private:
	void performDrag();
private:
	QPoint m_startPos;
	QPoint m_endPos;

};

#endif // COMMONLISTWIDGET_H
