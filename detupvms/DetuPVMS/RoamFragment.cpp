//
//  RoamFragment.cpp
//  MacQtPanoPlayerDemo
//
//  Created by chao on 2017/12/2.
//

#include <QApplication>
#include <QDir>
#include <qlogging.h>
#include <QString.h>
#include <QDebug>

#include "RoamFragment.h"

RoamFragment::RoamFragment(QObject *parent) : 
QObject(parent),
imageView_(NULL),
is_map_available_(false)
{

}

RoamFragment::~RoamFragment() {
    if(imageView_ != NULL) {
        delete imageView_;
        imageView_ = NULL;
    }
 
}

void RoamFragment::onCreate() {
    
}

void RoamFragment::onClick(View* view) {
    string tag = view->getTag();
	for (int i = 0; i < spy_list_.size(); i++)
	{
		if (tag == spy_list_[i].sIP.toStdString())
		{
			qDebug() << spy_list_[i].sIP;
			//通知显示枪机
			emit sigOnOpenGunCam(spy_list_[i]);
		}
		
	}


	emit sigOnOpenHotPic(QString::fromStdString(tag));



    if(tag == "ceshi0") {
        qDebug("this is the ceshi0 button onClick!");
	} else if (tag == "ceshi1") {
		qDebug("this is the ceshi1 button onClick!");
	} else if (tag == "ceshi10") {
		qDebug("this is the ceshi10 button onClick!");
	}
}

void RoamFragment::onCreateView(ViewGroup* container) 
{

	QFile pic_list(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map/hotPic/list.txt"));
	if (pic_list.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		while (!pic_list.atEnd())
		{

			QString temp = QString(pic_list.readLine());
			TargetInfo temp_info;
			int y = temp.right(temp.size()-temp.lastIndexOf("-")).toInt();
			temp = temp.left(temp.lastIndexOf("---"));
			int x = temp.right(temp.size() - temp.lastIndexOf("-")).toInt();
			temp = temp.left(temp.lastIndexOf("---"));

			imageView_ = new ImageView(container->getContext());
			imageView_->setOnClickListener(this);
			imageView_->setTag(temp.toStdString());

			QString point_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/point/hot_pic.png";
			siv_ = new SequenceImageView(container->getContext());

			imageView_->setFocusStateDrawableUrls(point_path.toLocal8Bit().data(), point_path.toLocal8Bit().data());
			LayoutParams* paramsIcon = new LayoutParams(0.05, 0.05);
			
			paramsIcon->ath = float(x) / 100.0;
			paramsIcon->atv = float(y) / 100.0;
			paramsIcon->displayType = DisplayType_GL_UN_DISTORTED;
			container->addView(imageView_, paramsIcon);
		}

		pic_list.close();
	}

	for (int i = 0; i < spy_list_.size(); i++)
	{
		imageView_ = new ImageView(container->getContext());
		imageView_->setTag(spy_list_[i].sIP.toStdString());
		imageView_->setOnClickListener(this);

		QString point_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/point/gunb.png";
		siv_ = new SequenceImageView(container->getContext());

		imageView_->setFocusStateDrawableUrls(point_path.toLocal8Bit().data(), point_path.toLocal8Bit().data());
		LayoutParams* paramsIcon = new LayoutParams(40, 40);
		paramsIcon->ath = float(spy_list_[i].pos_x) / 100.0;
		paramsIcon->atv = float(spy_list_[i].pos_y) / 100.0;
		//paramsIcon->rz = 45.0f;
		//container->addView(imageView_, paramsIcon);
	}
	
	if (is_map_available_)
	{
		imageView_ = new ImageView(container->getContext());
 		imageView_->setTag("ceshi0");
 		imageView_->setOnClickListener(this);
 
 		QString data_png_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/point/1.png";
 
 		imageView_->setFocusStateDrawableUrls(data_png_path.toLocal8Bit().data(), data_png_path.toLocal8Bit().data());
 		LayoutParams* paramsIcon = new LayoutParams(0.17, 0.17);
 		paramsIcon->ath = 0.0f;
 		paramsIcon->atv = 0.0f;
		paramsIcon->displayType = DisplayType_GL_DISTORTED;
 		//container->addView(imageView_, paramsIcon);


		imageView1_ = new ImageView(container->getContext());
		imageView1_->setTag("ceshi1");
		imageView1_->setOnClickListener(this);

		QString data_png_path1 = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/exhibition/people.png";

		imageView1_->setFocusStateDrawableUrls(data_png_path1.toLocal8Bit().data(), data_png_path1.toLocal8Bit().data());
		LayoutParams* paramsIcon1 = new LayoutParams(0.17, 0.17);
		paramsIcon1->ath = 1.0f;
		paramsIcon1->atv = 1.0f;
		paramsIcon1->displayType = DisplayType_GL_DISTORTED;
		//container->addView(imageView1_, paramsIcon1);



		QString point_path = QDir::homePath() + "/AppData/Local/Pano-VMS/Map/shizi/";
		siv_ = new SequenceImageView(container->getContext());
		vector<string> urls;
		for (int i = 1; i < 51; i++)
		{
			QString temp = point_path + QString::number(i) + ".png";
			urls.push_back(temp.toStdString());
		}
		siv_->setSequenceDrawableUrls(urls);

		siv_->setTag("ceshi10");
		siv_->setOnClickListener(this);


		LayoutParams* paramsCeshi = new LayoutParams(0.2, 0.2);
		paramsCeshi->ath = 0.0f;
		paramsCeshi->atv = 0.0f;
		paramsCeshi->displayType = DisplayType_GL_DISTORTED;
		container->addView(siv_, paramsCeshi);

	}

}
void RoamFragment::onDestroy() {
    
}

void RoamFragment::setPointInfo(QList<SpyInfo_t> spy_list)
{
	spy_list_ = spy_list;
}

void RoamFragment::setMapAvailable(bool is_map_available)
{
	is_map_available_ = is_map_available;
}

void RoamFragment::setVisible(int visible)
{
	imageView1_->setVisibility(visible);
}
