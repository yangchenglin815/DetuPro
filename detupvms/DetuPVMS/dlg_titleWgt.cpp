#include "dlg_titleWgt.h"
#include "ui_dlg_titleWgt.h"

dlg_titleWgt::dlg_titleWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dlg_titleWgt)
{
    ui->setupUi(this);
    initConnect();
	ui->closeBtn->setFocusPolicy(Qt::NoFocus);
}

dlg_titleWgt::~dlg_titleWgt()
{

}

void dlg_titleWgt::setLabelText(QString str)
{
    ui->label->setText(str);
}

void dlg_titleWgt::setHideCloseBtn(bool isHidden)
{
	ui->closeBtn->setHidden(isHidden);
}

void dlg_titleWgt::initConnect()
{
   connect(ui->closeBtn, SIGNAL(clicked()), this, SIGNAL(sigonClose()));
}
