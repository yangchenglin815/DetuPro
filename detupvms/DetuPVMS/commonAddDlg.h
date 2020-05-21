#ifndef COMMONADDDLG_H
#define COMMONADDDLG_H

#include <QDialog>
#include <QListWidget>
#include "ui_commonAddDlg.h"
#include "VRMap/VRMapAddDlgTitleWidget.h"
#include "VRMap/VRMapAddDlgListWgt.h"
#include "constStruct.h"

class commonAddDlg : public QDialog
{
	Q_OBJECT

public:
	explicit commonAddDlg(QWidget *parent = 0);
	~commonAddDlg();
	void setDlgTitleText(QString text);
	void setTabName(QString tabName_1, QString tabName_2);
	void setDlgType(int type);
	void initDeviceList(QList<deviceInfo> deviceList, QList<PanoSceneInfo> panoSceneList);
	void updateDeviceItem(QList<PanoMapPointInfo> panoInfoList);
	void removeOnMapItem(PanoMapPointInfo panoInfo);

	void initTab1Page();
	void initTab2Page();
signals:
	void sigOnGetPanoramaList(QList<PanoMapPointInfo_t> panoramaList);
private slots:
	void slotOnTab1Clicked(bool checked);
	void slotOnTab2Clicked(bool checked);
	void slotOnConfirmClicked();
	void slotOnItemClicked(QListWidgetItem* item);
	void slotOnSceneItemClicked(QListWidgetItem* item);
	void slotOnReportOnMapDevice(PanoMapPointInfo_t panoMapInfo);
	void slotOnStateChanged(int checkState);
	void slotOnStateSceneChanged(int checkState);
	void slotOnCancel();
private:
	void initConnect();
	void initData(int type);
	void setAddPanoramaDlg();
	void savePanoramaCameraData();
	void savePanoramaPictureData();
private:
	Ui::commonAddDlg ui;
	VRMapAddDlgTitleWidget *m_addDlgTiltWgt;
	VRMapAddDlgTitleWidget *m_addSceneTitWgt;
	QListWidget *m_listWgt;
	QListWidget *m_sceneListWgt;
	int m_currDlg_type;
	QList<deviceInfo> m_deviceList;
	QList<PanoSceneInfo> m_panoSceneList;
	QList<PanoMapPointInfo> m_panoramaList;

	QList<PanoMapPointInfo> m_onMap_panoramaList;

	//全景相机和场景项list
	QList<VRMapAddDlgListWgt*> panoCameraItemList;
	QList<VRMapAddDlgListWgt*> panoPictureItemList;
};

#endif // COMMONADDDLG_H
