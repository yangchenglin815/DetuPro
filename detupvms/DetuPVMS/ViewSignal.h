#ifndef VIEWSIGNAL_H
#define VIEWSIGNAL_H

#include <QObject>
#include "constStruct.h"

class ViewSignal : public QObject
{
	Q_OBJECT

public:
	static ViewSignal* instance();
signals:

	//通知缩放地图大小
	void sigOnResizeMap();

	void sigOnControlPlayerRecordFlv();
	void sigOnRebootM1ResetPlayer(int id);
	void sigOnCloseSubStreamClearPlayer(int id);
	void sigOnHandleSubStreamMessage(bool open, QString pvsId, int id);
	void sigOnDistributeList(const QList<deviceInfo> deviceList);
	void sigOnReportUpdateList(const QList<deviceInfo> deviceList);
	void sigOnReportOnMapDevice(PanoMapPointInfo_t panoramaInfo);

	void sigOnArrowClicked(int id);
	void sigOnMiniMapPointClicked(int id);

	void sigOnUpdateMapData();

	void sigOnReportTCSDisconnectError(std::string deviceID);
	void sigOnReportTCSOffLine(int serverId);

	void sigOnPicGroupOnClicked(PanoSceneInfo infoItem);
private:
	explicit ViewSignal(QObject *parent = 0);
	~ViewSignal();
private:
	static ViewSignal* m_pInstance;
};

#endif // VIEWSIGNAL_H
