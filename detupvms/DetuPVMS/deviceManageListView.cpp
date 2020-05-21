#include "deviceManageListView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QToolTip>

enum ItemType
{
	e_itemInfo = Qt::UserRole + 1,
};

deviceManageDelegate::deviceManageDelegate(QObject* parent)
{

}

void deviceManageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	painter->save();
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<deviceInfo>())
	{
		bool bSelected = false;
		if (option.state & QStyle::State_Selected)
		{
			bSelected = true;
// 			QRect rect = option.rect;
// 			rect.setX(rect.x());
// 			rect.setWidth(rect.width());
// 			painter->fillRect(rect, QBrush("#444444"));
		}
		deviceInfo deviceInfo_ = v_itemInfo.value<deviceInfo>();
		paintContent(painter, option, deviceInfo_, bSelected);
	}
	painter->restore();
}

void deviceManageDelegate::paintContent(QPainter *painter, const QStyleOptionViewItem &option, const deviceInfo &info, bool bSelected) const
{
	const int xPos = option.rect.x();
	const int yPos = option.rect.y();
	const int nWidth = option.rect.width();
	const int nHeight = option.rect.height();

	QFont font;
	font.setPixelSize(12);
	font.setFamily("微软雅黑");
	painter->setFont(font);
	QPen pen;
	pen.setColor("#eeeeee");
	painter->setPen(pen);

	//待绘制
	const int nLeftSpace = 28;
	// 序号
	const int nFirstWidth = 92;
	int nFirstXPos = xPos + nLeftSpace;
	QRect firstRect1(nFirstXPos, yPos, nFirstWidth, nHeight);
	painter->drawText(firstRect1, Qt::AlignLeft | Qt::AlignVCenter, QString::number(info.id));

	//
	const int nSecondWidth = 105;
	int nSecondXPos = nFirstXPos + nFirstWidth;
	QRect secondRect(nSecondXPos-8, yPos+16, 40, 20);
	QString status;
	if (info.status){
		status = QStringLiteral("在线");
		pen.setColor("#323434");
		painter->drawPixmap(secondRect, QPixmap(":/image/image/online.png"));
	}
	else
	{
		status = QStringLiteral("离线");
		pen.setColor("#eeeeee");
		painter->drawPixmap(secondRect, QPixmap(":/image/image/offline.png"));
	}
	painter->setPen(pen);
	painter->drawText(QRect(nSecondXPos, yPos+15, 40, 20), Qt::AlignLeft | Qt::AlignVCenter, status);

	//
	pen.setColor("#eeeeee");
	painter->setPen(pen);
	const int nThirdWidth = 130;
	int nThirdXPos = nSecondXPos + nSecondWidth;
	QRect thirdRect(nThirdXPos, yPos, nThirdWidth, nHeight);
	painter->drawText(thirdRect, Qt::AlignLeft | Qt::AlignVCenter, info.name);

	//
	const int nFourthWidth = 150;
	int nFourthXPos = nThirdXPos + nThirdWidth;
	QRect fourthRect(nFourthXPos, yPos, nFourthWidth, nHeight);
	painter->drawText(fourthRect, Qt::AlignLeft | Qt::AlignVCenter, info.serialNo);

	const int nFifthWidth = 115;
	int nFifthXPos = nFourthXPos + nFourthWidth;
	QRect fifthRect(nFifthXPos, yPos, nFirstWidth, nHeight);
	painter->drawText(fifthRect, Qt::AlignLeft | Qt::AlignVCenter, info.m1DeviceId);

	//
	const int nSixthWidth = 20;
	int nSixthXPos = nFifthXPos + nFifthWidth;
	QRect sixthRect(nSixthXPos, yPos + 16, 16, 16);
	if (info.status)
	{
		painter->drawPixmap(sixthRect, QPixmap(":/image/image/setup.png"));
	}
	else
	{
		painter->drawPixmap(sixthRect, QPixmap(":/image/image/setupb.png"));
	}

	if (info.status)
	{
		painter->drawPixmap(QRect(nSixthXPos + 46, yPos + 16, 16, 16), QPixmap(":/image/image/binding.png"));
	}
	else
	{
		painter->drawPixmap(QRect(nSixthXPos + 46, yPos + 16, 16, 16), QPixmap(":/image/image/bindingb.png"));
	}

	if (info.status)
	{
		painter->drawPixmap(QRect(nSixthXPos + 46 * 2, yPos + 16, 16, 16), QPixmap(":/image/image/live.png"));
	}
	else
	{
		painter->drawPixmap(QRect(nSixthXPos + 46 * 2, yPos + 16, 16, 16), QPixmap(":/image/image/liveb.png"));
	}

	if (info.status)
	{
		painter->drawPixmap(QRect(nSixthXPos + 46 * 3, yPos + 16, 16, 16), QPixmap(":/image/image/QR.png"));
	}
	else
	{
		painter->drawPixmap(QRect(nSixthXPos + 46 * 3, yPos + 16, 16, 16), QPixmap(":/image/image/QRb.png"));
	}

	//
	pen.setColor("#444444");
	pen.setWidth(1);
	painter->setPen(pen);
	painter->drawLine(xPos, yPos + nHeight - 1, xPos + nWidth, yPos + nHeight - 1);
}


bool deviceManageDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	int setupX = option.rect.x() + 28 + 92 + 105 + 130 + 150 + 115;
	int bindX = setupX + 46;
	int liveX = bindX + 46;
	int QRX = liveX + 46;
	int y = option.rect.y() + 16;
	QRect setupRect = QRect(setupX, y, 16, 16);
	QRect bindRect = QRect(bindX, y, 16, 16);
	QRect liveRect = QRect(liveX, y, 16, 16);
	QRect QRRect = QRect(QRX, y, 16, 16);

	QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
	if (event->type() == QEvent::MouseMove && setupRect.contains(mouseEvent->pos()))
	{
		QCursor cursor(Qt::PointingHandCursor);
		QApplication::setOverrideCursor(cursor);
		QString strText = QStringLiteral("设置");
		QToolTip::showText(mouseEvent->globalPos(), strText);
	}
	else if (event->type() == QEvent::MouseMove && bindRect.contains(mouseEvent->pos()))
	{
		QCursor cursor(Qt::PointingHandCursor);
		QApplication::setOverrideCursor(cursor);
		QString strText = QStringLiteral("绑定设备");
		QToolTip::showText(mouseEvent->globalPos(), strText);
	}
	else if (event->type() == QEvent::MouseMove && liveRect.contains(mouseEvent->pos()))
	{
		QCursor cursor(Qt::PointingHandCursor);
		QApplication::setOverrideCursor(cursor);
		QString strText = QStringLiteral("直播");
		QToolTip::showText(mouseEvent->globalPos(), strText);
	}
	else if (event->type() == QEvent::MouseMove && QRRect.contains(mouseEvent->pos()))
	{
		QCursor cursor(Qt::PointingHandCursor);
		QApplication::setOverrideCursor(cursor);
		QString strText = QStringLiteral("扫码观看");
		QToolTip::showText(mouseEvent->globalPos(), strText);
	}
	else
	{
		QCursor cursor(Qt::ArrowCursor);
		QApplication::setOverrideCursor(cursor);
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}

deviceManageListView::deviceManageListView(QWidget *parent)
	: QListView(parent)
	, m_pStandardItemModel(NULL)
	, m_nItemHeight(51)
	, m_nSelectKeyId(-1)
{
	init();
}

deviceManageListView::~deviceManageListView()
{

}

void deviceManageListView::appendItem(const deviceInfo &info)
{
	if (m_pStandardItemModel == NULL)
	{
		return;
	}

	QStandardItem* pItem = NULL;
	if (!m_ItemKeyIdMap.contains(info.id))
	{
		pItem = new QStandardItem;
		m_ItemKeyIdMap.insert(info.id, pItem);
		m_pStandardItemModel->appendRow(pItem);
		pItem->setSizeHint(QSize(0, m_nItemHeight));
	}
	else
	{
		pItem = m_ItemKeyIdMap.value(info.id);
	}

	QVariant variant;
	variant.setValue(info);
	pItem->setData(variant, e_itemInfo);

	if (m_nSelectKeyId == info.id)
	{
		this->setCurrentIndex(pItem->index());
	}
}

void deviceManageListView::clearItems()
{
	if (m_pStandardItemModel != NULL)
	{
		m_pStandardItemModel->clear();
		m_ItemKeyIdMap.clear();
	}
}

int deviceManageListView::getSelectIdList()
{
	return m_nSelectKeyId;
}

void deviceManageListView::setSelectKeyId(int nKeyId)
{
	m_nSelectKeyId = nKeyId;
}

void deviceManageListView::mousePressEvent(QMouseEvent *event)
{
	//获取选中状态
	QModelIndex index = indexAt(event->pos());

	deviceInfo deviceInfo_;
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<deviceInfo>())//可以转换
	{
		deviceInfo_ = v_itemInfo.value<deviceInfo>();
		m_nSelectKeyId = deviceInfo_.id;
		int x = event->pos().x();
		int y = event->pos().y();
		if (deviceInfo_.status)
		{
			if (x > 615 && x < 640)
			{
				//触发设置按钮
				emit sigOnSetup(deviceInfo_);
			}
			else if (x > 658 && x < 685)
			{
				//触发绑定球机
				emit sigOnBindDevice(deviceInfo_);
				//emit sigOnDownMove(deviceInfo_);
			}
			else if (x > 705 && x < 731)
			{
				//触发直播功能
				emit sigOnLiveShow(deviceInfo_);
				//emit sigOnUpMove(deviceInfo_);
			}
			else if (x > 751 && x < 777)
			{
				//触发扫码功能
				emit sigOnScanCode(deviceInfo_);
				//emit sigOnClicked(deviceInfo_);
			}
		}
	}
	QListView::mousePressEvent(event);
}

void deviceManageListView::init()
{
	setMouseTracking(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setItemDelegateForColumn(0, new deviceManageDelegate(this));
	setEditTriggers(QAbstractItemView::NoEditTriggers); // 只读
	m_pStandardItemModel = new QStandardItemModel(this);
	this->setModel(m_pStandardItemModel);
}
