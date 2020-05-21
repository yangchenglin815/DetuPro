#ifndef PTZMANAGELISTVIEW_H
#define PTZMANAGELISTVIEW_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "constStruct.h"

class ptzManageDelegate : public QStyledItemDelegate
{
public:
	ptzManageDelegate(QObject* parent = NULL);
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
	void paintContent(QPainter *painter, const QStyleOptionViewItem &option,
		const PtzInfo &info, bool bSelected) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

class ptzManageListView : public QListView
{
	Q_OBJECT

public:
	explicit ptzManageListView(QWidget *parent = 0);
	~ptzManageListView();
	void appendItem(const PtzInfo &info);
	void clearItems();
	int getSelectIdList();
	void setSelectKeyId(int nKeyId);
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void sigOnDeletePtz(PtzInfo info);
private:
	QStandardItemModel* m_pStandardItemModel;
	QMap<int, QStandardItem*> m_ItemKeyIdMap;
	QList<PtzInfo> m_ptzInfoList;
	int m_nItemHeight;
	int m_nSelectKeyId;
private:
	void init();
};
#endif // PTZMANAGELISTVIEW_H
