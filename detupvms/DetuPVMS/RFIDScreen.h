#ifndef RFIDREPORTER_H
#define RFIDREPORTER_H

#include <QWidget>
#include "ui_rfidscreen.h"

class RFIDScreen : public QWidget
{
	Q_OBJECT

public:
	RFIDScreen(QWidget *parent = 0);
	~RFIDScreen();
signals:
	void SignalToSetSwtichScreen(int button_num);

public slots:
	void OnPushButton1ClickedSlot();
	void OnPushButton2ClickedSlot();
	void OnPushButton3ClickedSlot();
	void OnPushButton4ClickedSlot();

	//œ‘ æUI
	void slotOnShowRFID(int type, int equip_id);
private:
	Ui::RFIDScreen ui;
};

#endif // RFIDREPORTER_H
