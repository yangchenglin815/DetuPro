#ifndef VRMAPWIDGET_H
#define VRMAPWIDGET_H

#include <QWidget>
#include "ui_VRMapWidget.h"
#include "commonAddDlg.h"
#include "constStruct.h"
#include "commonTipDlg.h"
#include "panoramaItemWidget.h"

class VRMapWidget : public QWidget
{
	Q_OBJECT

public:
	VRMapWidget(QWidget *parent = 0);
	~VRMapWidget();
private slots:
	void slotOnAddPanoramaBtnClicked();

	//ÃÌº”°¢…Ë÷√µÿÕº
	void slotOnAddMapBtnClicked();

	void slotOnRemoveOnMapDevice(PanoMapPointInfo_t panoInfo);

	void slotOnGetDeviceList(const QList<deviceInfo> deviceList);

	void slotOnGetPanoramaList(QList<PanoMapPointInfo_t> panoramaList);
	void slotItemSelected(QListWidgetItem *current, QListWidgetItem *previous);
	void slotOnDeleteItem();
	void slotOnTipDlgConfirm();

	void slotOnUpdateMapData();

	void slotOnResizeControlMap();
	void slotOnModifyState(int id);
private:
	void init();
	void initConnect();
private:
	Ui::VRMapWidget ui;
	commonAddDlg *m_addDlag;
	commonTipDlg *m_tipDlg;

	QList<deviceInfo> m_deviceList;
	QList<PanoSceneInfo> m_panoSceneList;

	QList<PanoMap_t> m_panoMapList;

	PanoMap_t current_map_;

	QString current_filePath_;

	QList<panoramaItemWidget*> m_listWgtItemList;


	bool is_map_load_;
};

#endif // VRMAPWIDGET_H
