/************************************************
* \file commonDlg.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* µÇÂ¼µ¯¿ò
************************************************/
#ifndef COMMONDLG_H
#define COMMONDLG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class commonDlg;
}

class commonDlg : public QDialog
{
    Q_OBJECT

public:
    explicit commonDlg(QWidget *parent = 0);
    ~commonDlg();
    void setTitleLabel(QString str);
	void setLoginDlg();
	void setCloseBtn(bool isHidden);
	void setBtnState();
	void clearPasswd();
	void setUnlockDlg();
	void setAboutDlg();
	void setSettingDlg();
	void setServerSettingDlg();
	void serverConnectFailed();
	void setUserName();
protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
signals:
	void sigOnFirstFinish();
	void sigOnLogin();
	void sigOnClose();
	void sigOnServerFinished();
	void sigOnReturnLock();
	void sigOnCloseUnlock();
private slots:
void slotOnSetDlgModal(bool modal);
void slot_dlgClose();
private:
    void init();
    void initConnect();
private:
    Ui::commonDlg *ui;
	QPoint lastMousePos_;
	bool isDraggingWindow_;
};

#endif // COMMONDLG_H
