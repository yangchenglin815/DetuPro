/************************************************
* \file deviceManageListView.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* �豸�������豸�б��ƴ���
************************************************/
#ifndef DEVICEMANAGELISTVIEW_H
#define DEVICEMANAGELISTVIEW_H

#include <QListView>
#include <QStyledItemDelegate>
#include <QStandardItemModel>
#include "constStruct.h"

class deviceManageDelegate : public QStyledItemDelegate
{
public:
	deviceManageDelegate(QObject* parent = NULL);
	void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;

private:
	void paintContent(QPainter *painter, const QStyleOptionViewItem &option,
		const deviceInfo &info, bool bSelected) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

class deviceManageListView : public QListView
{
	Q_OBJECT

public:
explicit deviceManageListView(QWidget *parent = 0);
	~deviceManageListView();
	void appendItem(const deviceInfo &info);
	void clearItems();
	int getSelectIdList();
	void setSelectKeyId(int nKeyId);
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void sigOnSetup(deviceInfo info);
	void sigOnDownMove(deviceInfo info);
	void sigOnUpMove(deviceInfo info);
	void sigOnClicked(deviceInfo info);
	void sigOnScanCode(deviceInfo info);     //ɨ�밴�������ź�
	void sigOnBindDevice(deviceInfo info);    //���豸�����ź�
	void sigOnLiveShow(deviceInfo info);
private:
	QStandardItemModel* m_pStandardItemModel;
	QMap<int, QStandardItem*> m_ItemKeyIdMap;
	QList<deviceInfo> m_deviceInfoList;
	int m_nItemHeight;
	int m_nSelectKeyId;
private:
	void init();
};

#endif // DEVICEMANAGELISTVIEW_H
