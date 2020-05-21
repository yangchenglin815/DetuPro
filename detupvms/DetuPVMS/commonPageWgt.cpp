#include <QMouseEvent> 

#include "commonPageWgt.h"
#include "ui_commonPageWgt.h"

commonPageWgt::commonPageWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commonPageWgt)
{
    ui->setupUi(this);
	//setAttribute(Qt::WA_TranslucentBackground);
}

commonPageWgt::~commonPageWgt()
{

}

void commonPageWgt::setImageAndText(QString tittle, QString content, QString iconPath, commonPageWgt::ConsoleButton type)
{
	type_ = type;
	ui->label->setStyleSheet(iconPath);
	ui->tittleLabel_->setText(tittle);
	ui->contentLabel_->setText(content);
}

void commonPageWgt::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit TrigConsoleButtonClicked(type_);
	}
}
