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

	//���ñ���Ԥ�õ㰴ť�ɲ��ɼ�
	void setSavePresetBtnVisible(bool visible);
	//�����л���С��ť�ɲ��ɼ�
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
