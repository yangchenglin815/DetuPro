/************************************************
* \file homewgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ������
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
	void sigOnSelectWarning();   //��ѡ����������ź�
	void sigOnBindPTZFailed();  //�����ʧ���ź�
	void sigOnBindPTZWarning();  //���δ���ź�
	void sigOnOptMizeSuccess();
	//�л�widget�źţ�֪ͨ���������Ƿ���벥��
	//void sigOnSwitchSocket();

	//��ʱ֪ͨ��ͼ���棬�ж��Ƿ������˵�ͼ
	void sigOnSetMapView();

protected:
	bool eventFilter(QObject *watched, QEvent *event);
public slots:
	void TabSupButtonClickedSlot(supTabWidget::supTabWgtButton type);
	void TabConsoleButtonClickedSlot();
	void ConsoleButtonClickedSlot(commonPageWgt::ConsoleButton type);
	void slot_tabClosed(supTabWidget::supTabWgtButton type);
	void slotOnDistributeList(QList<deviceInfo> deviceList);
	void slotOnStepOnMapSettings();   //��ת��VR��ͼ����ҳ��

	void slotOnSetFullScreen(bool is_full_screen);
private:
    void init();
	void initConnect();
private:
    Ui::homeWgt *ui;
	boost::shared_ptr<boost::thread> query_video_thread_;
};

#endif // HOMEWGT_H
