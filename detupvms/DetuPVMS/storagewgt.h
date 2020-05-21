#ifndef STORAGEWGT_H
#define STORAGEWGT_H

#include <QWidget>
#include <QTimer>
#include "ui_storagewgt.h"
#include "constStruct.h"
#include "waitWidget.h"
#include "diskFormatDlg.h"

class storageWgt : public QWidget
{
	Q_OBJECT

public:
	storageWgt(QWidget *parent = 0);
	~storageWgt();
	void initData(const QList<deviceInfo> &itemInfoList);
	void getSelectId(int selectId);
	void updateDeviceList(QList<deviceInfo> deviceList);
	void refreshDisk();
	void getDiskSize();
signals:
	void sigOnUpdate();
private slots:
	void slotOnRefresh();
	void slotOnDiskFormat();
	void slotDiskFormat();
	void slotOnSetDiskFormat(bool is_ok);
	void slotOnCheckFormatResult();
	void slotOnGetDiskSize();
	void slotOnRefreshStatus();
private:
	void init();
	void initConnect();
	void generateUI();
	void requestDiskSize();
	void requestDiskFormat();
private:
	Ui::storageWgt ui;
	QList<deviceInfo> m_InfoList;
	int m_selectId;
	QList<int> m_selectedId;
	waitWidget *waitDlg_;
	diskFormatDlg *formatDlg_;
	QTimer *timer_;
	bool isUpdate_;   //更新列表

	boost::shared_ptr<boost::thread> get_disk_thread_;
	boost::shared_ptr<boost::thread> format_disk_thread_;

};

#endif // STORAGEWGT_H
