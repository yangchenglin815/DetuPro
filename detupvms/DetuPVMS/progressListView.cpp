#include "progressListView.h"
#include "commonFun.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>
#include <QDebug>

enum ItemType
{
	e_itemInfo = Qt::UserRole + 1,
};

progressListView::progressListView(QWidget *parent)
	: QListView(parent)
	, m_pStandardItemModel(NULL)
	, m_nItemHeight(51)
	, m_nSelectKeyId(-1)
{
	init();
}

void progressListView::appendItem(const m_replayInfoList &m_info)
{
	if (m_pStandardItemModel == NULL)
	{
		return;
	}

	QStandardItem* pItem = NULL;
	if (!m_ItemKeyIdMap.contains(m_info.id))
	{
		pItem = new QStandardItem;
		m_ItemKeyIdMap.insert(m_info.id, pItem);
		m_pStandardItemModel->appendRow(pItem);
		pItem->setSizeHint(QSize(0, m_nItemHeight));
	}
	else
	{
		pItem = m_ItemKeyIdMap.value(m_info.id);
	}

	QVariant variant;
	variant.setValue(m_info);
	pItem->setData(variant, e_itemInfo);

	if (m_nSelectKeyId == m_info.id)
	{
		this->setCurrentIndex(pItem->index());
	}
}

void progressListView::clearItems()
{
	if (m_pStandardItemModel != NULL)
	{
		m_pStandardItemModel->clear();
		m_ItemKeyIdMap.clear();
	}
}

progressListView::~progressListView()
{

}

int progressListView::getSelectIdList()
{
	return m_nSelectKeyId;
}

void progressListView::setSelectKeyId(int nKeyId)
{
	m_nSelectKeyId = nKeyId;
}

void progressListView::mousePressEvent(QMouseEvent *event)
{
	QListView::mousePressEvent(event);
	//获取选中状态
	QModelIndex index = indexAt(event->pos());

	m_replayInfoList m_info;
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<m_replayInfoList>())//可以转换
	{
		m_info = v_itemInfo.value<m_replayInfoList>();
		m_nSelectKeyId = m_info.id;
		emit sigClickItem(m_info);
	}
}

void progressListView::init()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setItemDelegateForColumn(0, new progressDelegate(this));
	setEditTriggers(QAbstractItemView::NoEditTriggers); // 只读
	m_pStandardItemModel = new QStandardItemModel(this);
	this->setModel(m_pStandardItemModel);
}

progressDelegate::progressDelegate(QObject* parent)
: QStyledItemDelegate(parent)
{

}

void progressDelegate::paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	painter->save();
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<m_replayInfoList>())
	{
		bool bSelected = false;
		if (option.state & QStyle::State_Selected)
		{
			bSelected = true;
		}
		m_replayInfoList m_info = v_itemInfo.value<m_replayInfoList>();
		paintContent(painter, option, m_info, bSelected);
	}
	painter->restore();
}

void progressDelegate::paintContent(QPainter *painter, const QStyleOptionViewItem &option, const m_replayInfoList &m_info, bool BSelected) const
{
	const int xPos = option.rect.x();
	const int yPos = option.rect.y();
	const int nWidth = option.rect.width();
	const int nHeight = option.rect.height();
	const int nHour = 24*60;
	float per_hour = nWidth*1.0 / nHour;
	int count = m_info.m_infoList.length();
	for (int i = 0; i < count; i++){
		QString startDate = QDateTime::fromTime_t(m_info.m_infoList[i].startTime).toString("hh:mm:ss");
		QString endDate = QDateTime::fromTime_t(m_info.m_infoList[i].endTime).toString("hh:mm:ss");
		QString startDate_ = QDateTime::fromTime_t(m_info.m_infoList[i].startTime).toString("hh:mm");
		int scale = commonFun::timeExchange(startDate_, 1);
		float space = per_hour * scale;
		float  Offx = (m_info.m_infoList[i].endTime - m_info.m_infoList[i].startTime) / 60  * per_hour;

		painter->setBrush(QBrush("#a6abab", Qt::SolidPattern));
		QFont font;
		font.setPixelSize(10);
		painter->setFont(font);
		QPen pen;
		pen.setColor("#a6abab");
		painter->setPen(pen);
		painter->drawRect(xPos + space, yPos + 5, Offx, 10);
// 		QRect rect(xPos + space, yPos + 5 + 12, 50, 10);
// 		painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, startDate);
// 		QRect rect1(xPos + space + Offx - 45, yPos + 5 + 12, 50, 10);
// 		painter->drawText(rect1, Qt::AlignLeft | Qt::AlignVCenter, endDate);
	}

// 	QString startDate = QDateTime::fromTime_t(m_info.startTime).toString("hh:mm:ss");
// 	QString endDate = QDateTime::fromTime_t(m_info.endTime).toString("hh:mm:ss");
// 	int  scale = QDateTime::fromTime_t(m_info.startTime).toString("hh").toInt();
// 	int space = per_hour * scale;
// 	int  Offx = (m_info.endTime - m_info.startTime) / 60/60*per_hour;
// 	painter->setBrush(QBrush("#a6abab", Qt::SolidPattern));
// 	QFont font;
// 	font.setPixelSize(10);
// 	painter->setFont(font);
// 	QPen pen;
// 	pen.setColor("#a6abab");
// 	painter->setPen(pen);
//     
// 	painter->drawRect(xPos + space, yPos + 5, Offx, 10);
// 	QRect rect(xPos + space, yPos + 5 + 12, 50, 10);
// 	painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, startDate);
// 	QRect rect1(xPos + space + Offx - 45, yPos + 5 + 12, 50, 10);
// 	painter->drawText(rect1, Qt::AlignLeft | Qt::AlignVCenter, endDate);
}
