/************************************************
* \file progressListView.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ½ø¶ÈÌõ
************************************************/
#ifndef PROGRESSLISTVIEW_H
#define PROGRESSLISTVIEW_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "constStruct.h"
#include "CurrentLineItem.h"

class progressDelegate : public QStyledItemDelegate
{
public:
	progressDelegate(QObject* parent = NULL);
	void paint(QPainter *painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
private:
	void paintContent(QPainter *painter, const QStyleOptionViewItem &option,
		const m_replayInfoList &m_info, bool BSelected) const;
};

class progressListView : public QListView
{
	Q_OBJECT

public:
	explicit progressListView(QWidget *parent = 0);
	void  appendItem(const m_replayInfoList &m_info);
	void clearItems();
	~progressListView();
	int getSelectIdList();
	void setSelectKeyId(int nKeyId);

protected:
	void mousePressEvent(QMouseEvent *event);

signals:
	void sigClickItem(m_replayInfoList m_info);
private:
	QStandardItemModel* m_pStandardItemModel;
	QMap<int, QStandardItem*> m_ItemKeyIdMap;
	int m_nItemHeight;
	QList<m_replayInfoList> m_infoList;
	int m_nSelectKeyId;

private:
	void init();
};

#endif // PROGRESSLISTVIEW_H
