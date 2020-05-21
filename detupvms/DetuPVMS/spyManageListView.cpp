#include "spyManageListView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QToolTip>

enum ItemType
{
	e_itemInfo = Qt::UserRole + 1,
};

spyManageListView::spyManageListView(QWidget *parent)
	: QListView(parent)
	, m_pStandardItemModel(NULL)
	, m_nItemHeight(51)
	, m_nSelectKeyId(-1)
{
	init();
}

spyManageListView::~spyManageListView()
{

}

void spyManageListView::appendItem(const SpyInfo &info)
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

void spyManageListView::clearItems()
{
	if (m_pStandardItemModel != NULL)
	{
		m_pStandardItemModel->clear();
		m_ItemKeyIdMap.clear();
	}
}

int spyManageListView::getSelectIdList()
{
	return m_nSelectKeyId;
}

void spyManageListView::setSelectKeyId(int nKeyId)
{
	m_nSelectKeyId = nKeyId;
}

void spyManageListView::mousePressEvent(QMouseEvent *event)
{
	QListView::mousePressEvent(event);
	//获取选中状态
	QModelIndex index = indexAt(event->pos());

	SpyInfo spyInfo_;
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<SpyInfo>())//可以转换
	{
		spyInfo_ = v_itemInfo.value<SpyInfo>();
		m_nSelectKeyId = spyInfo_.id;
		int x = event->pos().x();
		int y = event->pos().y();
		if (x > 675 && x < 700)
		{
			emit sigOnDeleteSpy(spyInfo_);
		}
	}
}

void spyManageListView::init()
{
	setMouseTracking(true);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setItemDelegateForColumn(0, new spyManageDelegate(this));
	setEditTriggers(QAbstractItemView::NoEditTriggers); // 只读
	m_pStandardItemModel = new QStandardItemModel(this);
	this->setModel(m_pStandardItemModel);
}

spyManageDelegate::spyManageDelegate(QObject* parent /*= NULL*/)
{

}

void spyManageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	painter->save();
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<SpyInfo>())
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
		SpyInfo spyInfo_ = v_itemInfo.value<SpyInfo>();
		paintContent(painter, option, spyInfo_, bSelected);
	}
	painter->restore();
}

void spyManageDelegate::paintContent(QPainter *painter, const QStyleOptionViewItem &option, const SpyInfo &info, bool bSelected) const
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
	const int nFirstWidth = 165;
	int nFirstXPos = xPos + nLeftSpace;
	QRect firstRect1(nFirstXPos, yPos, nFirstWidth, nHeight);
	painter->drawText(firstRect1, Qt::AlignLeft | Qt::AlignVCenter, QString::number(info.id));

	//
	const int nSecondWidth = 255;
	int nSecondXPos = nFirstXPos + nFirstWidth;
	QRect secondRect(nSecondXPos, yPos, nSecondWidth, nHeight);
	painter->drawText(secondRect, Qt::AlignLeft | Qt::AlignVCenter, info.sIP);

	//
	const int nThirdWidth = 235;
	int nThirdXPos = nSecondXPos + nSecondWidth;
	QRect thirdRect(nThirdXPos, yPos, nThirdWidth, nHeight);
	painter->drawText(thirdRect, Qt::AlignLeft | Qt::AlignVCenter, QString::number(info.wPort));

	//
	const int nFourthWidth = 180;
	int nFourthXPos = nThirdXPos + nThirdWidth;
	QRect fourthRect(nFourthXPos, yPos + 16, 16, 16);
	painter->drawPixmap(fourthRect, QPixmap(":/image/image/delete.png"));

	//
	pen.setColor("#444444");
	pen.setWidth(1);
	painter->setPen(pen);
	painter->drawLine(xPos, yPos + nHeight - 1, xPos + nWidth, yPos + nHeight - 1);
}

bool spyManageDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
	int x = option.rect.x() + 28 + 165 + 255 + 235;
	int y = option.rect.y() + 16;
	QRect decorationRect = QRect(x, y, 16, 16);

	QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
	if (event->type() == QEvent::MouseMove && decorationRect.contains(mouseEvent->pos()))
	{
		QCursor cursor(Qt::PointingHandCursor);
		QApplication::setOverrideCursor(cursor);
		QString tip = QStringLiteral("删除枪机");
		QToolTip::showText(mouseEvent->globalPos(), tip);
	}
	else
	{
		QCursor cursor(Qt::ArrowCursor);
		QApplication::setOverrideCursor(cursor);
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
