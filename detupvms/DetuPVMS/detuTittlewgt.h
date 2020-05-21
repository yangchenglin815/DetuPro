/************************************************
* \file detuTittlewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 主界面标题栏窗口
************************************************/
#ifndef DETUTITTLEWGT_H
#define DETUTITTLEWGT_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class detuTittleWgt;
}

class detuTittleWgt : public QWidget
{
    Q_OBJECT

public:
    explicit detuTittleWgt(QWidget *parent = 0);
    ~detuTittleWgt();
    void setTimeShow(QString time);
	void setMaxBtnStatus(bool max);
	void setLockStyleSheet(bool lock);
	void getShowPos();
signals:
    void sigonCloseClient();
    void sigonMaxminzed();
    void sigonMinimized();
	void sigonUnlock();
	void sigonHelpPos(int x, int y);
	void sigonShowHelpDlg();
	void sigonCloseHelp();
	void sigOnShowSettingDlg();
	void sigOnDbClickTitle();
protected:
	bool eventFilter(QObject *watched, QEvent *event);
	void showEvent(QShowEvent *event);
private:
    void initConnect();
	void init();
private:
    Ui::detuTittleWgt *ui;
	int nXPos_;
	int nYPos_;
};

#endif // DETUTITTLEWGT_H
