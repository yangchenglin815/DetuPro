#ifndef STORAGETABWGT_H
#define STORAGETABWGT_H

#include <QWidget>
#include "ui_StorageTabWgt.h"

class StorageTabWgt : public QWidget
{
	Q_OBJECT

public:

	StorageTabWgt(QWidget *parent = 0);
	~StorageTabWgt();

	enum storageTabWgtButtonType
	{
		TabSet = 0,
		TabPlan = 1,
	};

public:
	void setTittle(QString tittle, StorageTabWgt::storageTabWgtButtonType type);
	void setSelectedStatus(bool selected);

protected:
	virtual void mousePressEvent(QMouseEvent *event);
signals:
	//tab上按钮点击事件
	void TrigStorageTabButtonClicked(StorageTabWgt::storageTabWgtButtonType type);

private:
	Ui::StorageTabWgt ui;
	storageTabWgtButtonType type_;
};

#endif // STORAGETABWGT_H
