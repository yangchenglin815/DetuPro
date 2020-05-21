#include "MapPointSetingWgt.h"

MapPointSetingWgt::MapPointSetingWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	init();
	initConnect();
}

MapPointSetingWgt::~MapPointSetingWgt()
{

}

void MapPointSetingWgt::init()
{

}

void MapPointSetingWgt::initConnect()
{
	connect(ui.GviewBtn_, SIGNAL(clicked()), this, SLOT(slotOnGviewBtnClicked()));
	connect(ui.ConnBtn_, SIGNAL(clicked()), this, SLOT(slotOnConnBtnClicked()));
	connect(ui.DeleteBtn_, SIGNAL(clicked()), this, SLOT(slotOnDeleteBtnClicked()));
}

void MapPointSetingWgt::slotOnGviewBtnClicked()
{
	this->hide();
	emit sigOnGviewBtnClicked();
}

void MapPointSetingWgt::slotOnConnBtnClicked()
{
	this->hide();
	emit sigOnConnBtnClicked();
}

void MapPointSetingWgt::slotOnDeleteBtnClicked()
{
	this->hide();
	emit sigOnDeleteBtnClicked();
}
