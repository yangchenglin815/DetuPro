#include "commonListWidget.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include "VRMap/panoramaItemWidget.h"
commonListWidget::commonListWidget(QWidget *parent)
	: QListWidget(parent)
{
	setAcceptDrops(true);
}

commonListWidget::~commonListWidget()
{

}

void commonListWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
		m_startPos = event->pos();
	QListWidget::mousePressEvent(event);
}

void commonListWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) {
		int distance = (event->pos() - m_startPos).manhattanLength();
		if (distance >= QApplication::startDragDistance())
			performDrag();
	}
	QListWidget::mouseMoveEvent(event);
}

void commonListWidget::dragEnterEvent(QDragEnterEvent *event)
{
// 	commonListWidget *source =
// 		qobject_cast<commonListWidget *>(event->source());
// 	if (source && source != this) {
// 		event->setDropAction(Qt::MoveAction);
// 		event->accept();
// 	}
}

void commonListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	commonListWidget *source =
		qobject_cast<commonListWidget *>(event->source());
    if (source && source != this) {
		event->setDropAction(Qt::MoveAction);
		event->accept();
	}
}

void commonListWidget::dropEvent(QDropEvent *event)
{
// 	commonListWidget *source =
// 		qobject_cast<commonListWidget *>(event->source());
// 	if (source && source != this) {
// 		m_endPos = event->pos();
// 		event->setDropAction(Qt::MoveAction);
// 		event->accept();
// 	}
// 	//·¢ÐÅºÅ
// 	emit sigOnAddMapPoint();
}

void commonListWidget::performDrag()
{
	QListWidgetItem *item = currentItem();
	if (item) {
		QMimeData *mimeData = new QMimeData;
		mimeData->setText(item->text());

		QWidget *wid = itemWidget(item);
		panoramaItemWidget *itemWgt = qobject_cast<panoramaItemWidget *>(wid);
		PanoMapPointInfo_t info_t;
		itemWgt->getItemData(info_t);
		QString pixPicture;
		if (info_t.map_point_type == PANOSCENE_ON_LINE)
		{
			pixPicture = ":/image/image/panoSceneOnLine.png";
		}
		else if (info_t.map_point_type == DEVICE_ON_LINE)
		{
			pixPicture = ":/image/image/panoDeviceOnLine.png";
		}

		QDrag *drag = new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(QPixmap(pixPicture));
		if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
			return;
	}
}
