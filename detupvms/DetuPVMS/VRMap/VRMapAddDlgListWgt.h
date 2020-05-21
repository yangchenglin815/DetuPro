#ifndef VRMAPADDDLGLISTWGT_H
#define VRMAPADDDLGLISTWGT_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include "constStruct.h"

class VRMapAddDlgListWgt : public QWidget
{
	Q_OBJECT

public:
	explicit VRMapAddDlgListWgt(QWidget *parent = 0);
	~VRMapAddDlgListWgt();
	void initAddPanoramaCamera(deviceInfo info);
	void initAddPanoramaScene(PanoSceneInfo info);
	void setItemChecked(bool checked);
	void onItemSelected();
	void getInfoBySelectedItem(deviceInfo &info);
	void getSceneBySelectedItem(PanoSceneInfo &info);
private:
	QLabel *m_labelName;
	QLabel *m_labelNo;
	QCheckBox *m_checkBox;
	deviceInfo m_deviceInfo;
	PanoSceneInfo m_PanoSceneInfo;
};

#endif // VRMAPADDDLGLISTWGT_H
