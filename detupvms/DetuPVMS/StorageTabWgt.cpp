#include <QMouseEvent> 

#include "StorageTabWgt.h"

StorageTabWgt::StorageTabWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

StorageTabWgt::~StorageTabWgt()
{

}

void StorageTabWgt::setTittle(QString tittle, storageTabWgtButtonType type)
{

}

void StorageTabWgt::setSelectedStatus(bool selected)
{

}

void StorageTabWgt::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit TrigStorageTabButtonClicked(type_);
	}
}
