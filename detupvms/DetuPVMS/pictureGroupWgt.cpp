#include "pictureGroupWgt.h"
#include "ui_pictureGroupWgt.h"
#include "ViewSignal.h"

#include <QStandardItem>
#include <QPushButton>
#include <QSpacerItem>
#include <QDebug>
#include <QLabel>
#include <QPainter>

pictureGroupWgt::pictureGroupWgt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pictureGroupWgt)
{
    ui->setupUi(this);

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(slotOnButtonClicked(int)));
	connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(slotOnCloseClicked()));
}

pictureGroupWgt::~pictureGroupWgt()
{
    delete ui;
}

void pictureGroupWgt::maskUI(QSize picSize, int space, bool isGird, PanoSceneInfo sceneInfo)
{
	ui->listWidget->clear();

    //设置QListWidget中的单元项的图片大小
    ui->listWidget->setIconSize(picSize);
    ui->listWidget->setResizeMode(QListView::Adjust);

    //设置Item是否一行显示
    ui->listWidget->setWrapping(isGird);

    //设置QListWidget的显示模式
    ui->listWidget->setViewMode(QListView::IconMode);
    //设置QListWidget中的单元项不可被拖动
    ui->listWidget->setMovement(QListView::Static);

    //设置QListWidget中的单元项的间距
    if(!isGird)
    {
		ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
         ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }
    else
    {
        ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    }
    ui->listWidget->setSpacing(space);

    //设置Item
    for(int nIndex = 0; nIndex < sceneInfo.sceneList.size(); ++nIndex)
    {
        //获得图片路径
        QString strPath = sceneInfo.sceneList[nIndex].Path;
        //生成图像objPixmap
        QPixmap objPixmap(strPath);
        //生成QListWidgetItem对象(注意：其Icon图像进行了伸缩)---scaled函数
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(picSize)),  sceneInfo.sceneList[nIndex].name);
        //设置单元项的宽度和高度
        pItem->setSizeHint(QSize(picSize.width() + 2, picSize.height() + 26));
        ui->listWidget->insertItem(nIndex, pItem);
		m_itemUrl.insert(nIndex, sceneInfo);
    }
}

void pictureGroupWgt::slotOnButtonClicked(int row)
{
    qDebug()<<"current selected image : "<<row<<"--------->"<<m_itemUrl[row].Path;
	m_itemUrl[row].currPicIndex = row;
	ViewSignal::instance()->sigOnPicGroupOnClicked(m_itemUrl[row]);
}

void pictureGroupWgt::slotOnCloseClicked()
{
	emit sigOnHiddenPicGroup();
}

