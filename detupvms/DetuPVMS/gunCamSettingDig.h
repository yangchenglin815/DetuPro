#ifndef GUNCAMSETTINGDIG_H
#define GUNCAMSETTINGDIG_H

#include <QWidget>
#include "ui_gunCamSettingDig.h"

#include "constStruct.h"

class gunCamWgt;
class gunCamMiniItem;

class gunCamSettingDig : public QWidget
{
	Q_OBJECT

public:
	gunCamSettingDig(QWidget *parent = 0);
	~gunCamSettingDig();

	void init();
	void initConnect();

	void setTitleText(const SpyInfo &curr_info);
	void setTitleText(QString tittle);
	void setPosSet(int x, int y);

	void showGunCam();
	void showHotPic();


private slots:
	void slotOnConfirm();
	void slotOnCancel();

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	Ui::gunCamSettingDig ui;

	SpyInfo m_curr_spyInfo;

	gunCamMiniItem *gun_cam_mini_item_;
	gunCamWgt *gunWgt_;

	QPoint delta_pos_;
	QPoint last_pos_;

	bool is_cun_cam_;
	bool is_hot_pic_;

};

#endif // GUNCAMSETTINGDIG_H
