//
//  RoamFragment.hpp
//  MacQtPanoPlayerDemo
//
//  Created by chao on 2017/12/2.
//

#ifndef RoamFragment_hpp
#define RoamFragment_hpp

#include <stdio.h>
#include <QObject>

#include "Fragment.h"
#include "ImageView.h"
#include "FrameLayout.h"
#include "SequenceImageView.h"

#include "constStruct.h"

using namespace DetuPanoPlayer;

class RoamFragment : public QObject,public Fragment, public View::OnClickListener
{
	Q_OBJECT
public:
    ImageView* imageView_;
	ImageView* imageView1_;
	ImageView* imageView2;
	ImageView* imageView3;
    SequenceImageView* siv_;
	SequenceImageView* siv1_;

	explicit RoamFragment(QObject *parent = 0);

    ~RoamFragment();
    void onCreate();
    void onCreateView(ViewGroup* container);
    void onClick(View* view);
    void onDestroy();

	void setPointInfo(QList<SpyInfo_t> spy_list);

	void setMapAvailable(bool is_map_available);

	void setVisible(int visible);
signals:
	void sigOnOpenGunCam(SpyInfo_t spi_info);
	void sigOnOpenHotPic(QString path);

private:
	bool is_map_available_;

	QList<SpyInfo_t> spy_list_;
	 
};

#endif /* RoamFragment_hpp */
