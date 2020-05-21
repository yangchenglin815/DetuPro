/************************************************
* \file homewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* 主界面
************************************************/
#ifndef HOMEWGT_H
#define HOMEWGT_H

#include <QWidget>

#include "commonPageWgt.h"
#include "suptabwidget.h"

#include "APIProtocol.h"
#include "tcpclient.hpp"
#include "constStruct.h"

namespace Ui {
class homeWgt;
}

class homeWgt : public QWidget
{
    Q_OBJECT

public:
    explicit homeWgt(QWidget *parent = 0);
    ~homeWgt();
	void setCloseClient();
	void setServerOline(bool online);
	void setSpeedPos(int w);
	void clearPlayerStatus();
	void setPosMove();
	void closePreviewReplay();
	void closeMapPlay();
signals:
	void sigOnUpdate();
	void sigOnSelectWarning();   //空选择操作警告信号
	void sigOnBindPTZFailed();  //球机绑定失败信号
	void sigOnBindPTZWarning();  //球机未绑定信号
	void sigOnOptMizeSuccess();
	//切换widget信号，通知播放器是是否解码播放
	//void sigOnSwitchSocket();

	//临时通知地图界面，判断是否设置了地图
	void sigOnSetMapView();

protected:
	bool eventFilter(QObject *watched, QEvent *event);
public slots:
	void TabSupButtonClickedSlot(supTabWidget::supTabWgtButton type);
	void TabConsoleButtonClickedSlot();
	void ConsoleButtonClickedSlot(commonPageWgt::ConsoleButton type);
	void slot_tabClosed(supTabWidget::supTabWgtButton type);
	void slotOnDistributeList(QList<deviceInfo> deviceList);
	void slotOnStepOnMapSettings();   //跳转到VR地图设置页面

	void slotOnSetFullScreen(bool is_full_screen);
private:
    void init();
	void initConnect();
private:
    Ui::homeWgt *ui;
	boost::shared_ptr<boost::thread> query_video_thread_;
};

#endif // HOMEWGT_H
