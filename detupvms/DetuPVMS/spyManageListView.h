#ifndef SPYMANAGELISTVIEW_H
#define SPYMANAGELISTVIEW_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "constStruct.h"

class spyManageDelegate : public QStyledItemDelegate
{
public:
	spyManageDelegate(QObject* parent = NULL);
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
	void paintContent(QPainter *painter, const QStyleOptionViewItem &option,
		const SpyInfo &info, bool bSelected) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

class spyManageListView : public QListView
{
	Q_OBJECT
public:
    explicit spyManageListView(QWidget *parent = 0);
    ~spyManageListView();
	void appendItem(const SpyInfo &info);
	void clearItems();
	int getSelectIdList();
	void setSelectKeyId(int nKeyId);
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void sigOnDeleteSpy(SpyInfo info);
private:
	QStandardItemModel* m_pStandardItemModel;
	QMap<int, QStandardItem*> m_ItemKeyIdMap;
	QList<SpyInfo> m_spyInfoList;
	int m_nItemHeight;
	int m_nSelectKeyId;
private:
	void init();
};

#endif // SPYMANAGELISTVIEW_H
