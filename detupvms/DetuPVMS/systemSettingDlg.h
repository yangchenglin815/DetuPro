#ifndef SYSTEMSETTINGDLG_H
#define SYSTEMSETTINGDLG_H

#include <QDialog>
#include <QScrollBar>
#include <QMouseEvent>
#include "ui_systemSettingDlg.h"
/*using namespace dm::server;*/
class systemSettingDlg : public QDialog
{
	Q_OBJECT

public:
	systemSettingDlg(QDialog *parent = 0);
	~systemSettingDlg();
	void initData();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private slots:
	void slotOnSave();
	void slotOnSetCapturePath();
	void slotOnStepOnReset();
	void slotOnResetTCSConfig();

	void slotOnSetAdmin();
private:
	void init();
	void initConnect();
	void initSystemSettings();
	void initDecodeSettings();
	void initCaptureSettings();
	void initAdminSettings();

	void saveSystemSettings();
	void saveDecodeSettings();
	void saveBitStreamSettings();
	void saveCaptureSettings();
private:
	Ui::systemSettingDlg ui;
	QScrollBar *scrollBar_;
	QPoint lastMousePos_;
	bool isDraggingWindow_;
};

#endif // SYSTEMSETTINGDLG_H
