#ifndef STORAGELISTVIEW_H
#define STORAGELISTVIEW_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "constStruct.h"

class storageDelegate : public QStyledItemDelegate
{
public:
	storageDelegate(QObject* parent = NULL);
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
	void paintContent(QPainter *painter, const QStyleOptionViewItem &option,
		const deviceInfo &info, bool bSelected) const;
};

class storageListView : public QListView
{
	Q_OBJECT

public:
	explicit storageListView(QWidget *parent = 0);
	~storageListView();
	void appendItem(const deviceInfo &info);
	void clearItems();
	void clearSelectedIdList();
	QList<int> getSelectKeyId();
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void sigClickItem(deviceInfo info);
private:
	QStandardItemModel* m_pStandardItemModel;
	QMap<int, QStandardItem*> m_ItemKeyIdMap;
	QList<deviceInfo> m_deviceInfoList;
	int m_nItemHeight;
	QList<int> m_selectedIdList;
private:
	void init();
	
};

#endif // STORAGELISTVIEW_H
