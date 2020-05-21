#ifndef MP4EXPORTER_H
#define MP4EXPORTER_H

#include <QtWidgets/QMainWindow>
#include "ui_mp4exporter.h"

#include <memory>
#include <thread>

class MP4Exporter : public QMainWindow
{
	Q_OBJECT

public:
	MP4Exporter(QWidget *parent = 0);
	~MP4Exporter();

public slots:
	void onOpenFileButtonClick();
	void onExportButtonClick();
	void onExportBtnColoring(bool color);

signals:
	void ExportBtnColorSig(bool color);

private:
	int  ansi_to_utf8(const char* pszCode, char* UTF8code);
	void export_mp4(void);

private:
	Ui::MP4ExporterClass ui;

	QString m_file_path;
	int m_width;
	int m_height;
	int m_fps;
	int m_pos;
	int m_bitrate;
	bool m_is_color;

	std::shared_ptr<std::thread>	m_export_thread;
};

#endif // MP4EXPORTER_H
