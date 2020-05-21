#ifndef BALLCAMCTRL_H
#define BALLCAMCTRL_H

#include <QWidget>
#include "ui_ballcamctrl.h"

#include "GeneralDef.h"

class ballCamCtrl : public QWidget
{
	Q_OBJECT

public:
	ballCamCtrl(QWidget *parent = 0);
	~ballCamCtrl();
	void setButtonText(QString text, int type);

	//设置保存预置点按钮可不可见
	void setSavePresetBtnVisible(bool visible);
	//设置切换大小按钮可不可见
	void setExchangeBtnVisible(bool visible);
signals:
	void buttonPressed(int id);
	void buttonReleased(int id);
	void sigOnSavePoint();
private slots:
	void slotOnClicked();
private:
	Ui::ballCamCtrl ui;
	QString curr_point;
	int curr_type;
};

#endif // BALLCAMCTRL_H
