#include "storageListView.h"
#include <QPainter>
#include <QMouseEvent>

enum ItemType
{
	e_itemInfo = Qt::UserRole + 1,
};

storageListView::storageListView(QWidget *parent)
	: QListView(parent)
	, m_pStandardItemModel(NULL)
	, m_nItemHeight(48)
{
	init();
}

storageListView::~storageListView()
{

}

void storageListView::appendItem(const deviceInfo &info)
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

	if (m_selectedIdList.contains(info.id))
	{
		this->setCurrentIndex(pItem->index());
	}
}

void storageListView::clearItems()
{
	if (m_pStandardItemModel != NULL)
	{
		m_pStandardItemModel->clear();
		m_ItemKeyIdMap.clear();
		update();
	}
}

void storageListView::clearSelectedIdList()
{
	m_selectedIdList.clear();
}

QList<int>  storageListView::getSelectKeyId()
{
	return m_selectedIdList;
}

void storageListView::mousePressEvent(QMouseEvent *event)
{
	QListView::mousePressEvent(event);
	//获取选中状态
	QModelIndex index = indexAt(event->pos());

	deviceInfo deviceInfo_;
	QVariant v_itemInfo = index.data(e_itemInfo);
	if (v_itemInfo.canConvert<deviceInfo>())//可以转换
	{
		deviceInfo_ = v_itemInfo.value<deviceInfo>();
		if (m_selectedIdList.contains(deviceInfo_.id))
		{
			m_selectedIdList.removeAll(deviceInfo_.id);
		}
		else
		{
			m_selectedIdList.append(deviceInfo_.id);
		}
	}
}

void storageListView::init()
{
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setItemDelegateForColumn(0, new storageDelegate(this));
	setEditTriggers(QAbstractItemView::NoEditTriggers); // 只读
	setSelectionMode(QAbstractItemView::MultiSelection); //多选
	m_pStandardItemModel = new QStandardItemModel(this);
	this->setModel(m_pStandardItemModel);
}

storageDelegate::storageDelegate(QObject* parent /*= NULL*/)
{

}

void storageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
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

void storageDelegate::paintContent(QPainter *painter, const QStyleOptionViewItem &option, const deviceInfo &info, bool bSelected) const
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

	const int nLeftSpace = 20;
	//选择列
	const int checkBoxSideLenght = 12;
	int nSelectBoxXPos = xPos + nLeftSpace;
	int nSelectBoxYPos = yPos + (nHeight - checkBoxSideLenght)/2;
	QRect selectBoxRext(nSelectBoxXPos, nSelectBoxYPos, checkBoxSideLenght, checkBoxSideLenght);
	QPixmap checkBoxPixmap;
	checkBoxPixmap.load(bSelected ? ":/image/image/checked.png" : ":/image/image/unchecked.png");
	painter->drawPixmap(selectBoxRext, checkBoxPixmap);

	// 序号
	const int nFirstWidth = 112;
	int nFirstXPos = nSelectBoxXPos + checkBoxSideLenght + nLeftSpace + 8;
	QRect firstRect1(nFirstXPos, yPos, nFirstWidth, nHeight);
	painter->drawText(firstRect1, Qt::AlignLeft | Qt::AlignVCenter, QString::number(info.id));

	//
	const int nSecondWidth = 142;
	int nSecondXPos = nFirstXPos + nFirstWidth;
	QRect secondRect(nSecondXPos, yPos, nSecondWidth, nHeight);
	painter->drawText(secondRect, Qt::AlignLeft | Qt::AlignVCenter, info.name);

	//
	const int nThirdWidth = 200;
	int nThirdXPos = nSecondXPos + nSecondWidth;
	QRect thirdRect(nThirdXPos, yPos, nThirdWidth, nHeight);
	painter->drawText(thirdRect, Qt::AlignLeft | Qt::AlignVCenter, info.serialNo);

	//
	const int nFourthWidth = 180;
	int nFourthXPos = nThirdXPos + nThirdWidth;
	QRect fourthRect(nFourthXPos, yPos, nFourthWidth, nHeight);
	int usedRoom = info.usedRoom / 1024;
	painter->drawText(fourthRect, Qt::AlignLeft | Qt::AlignVCenter, QString::number(usedRoom));

	//
	const int nFifthWidth = 80;
	int nFifthXPos = nFourthXPos + nFourthWidth;
	QRect fifthRect(nFifthXPos, yPos, nFifthWidth, nHeight);
	int totalRoom = info.usingRoom / 1024;
	painter->drawText(fifthRect, Qt::AlignLeft | Qt::AlignVCenter, QString::number(totalRoom));

	//
	pen.setColor("#444444");
	pen.setWidth(1);
	painter->setPen(pen);
	painter->drawLine(xPos, yPos + nHeight - 1, xPos + nWidth, yPos + nHeight - 1);
}
