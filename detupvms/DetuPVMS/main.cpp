#include <QApplication>
#include <QWidget>
#include <QDir>
#include <QString>
#include <QIcon>
#include <QTextCodec>
#include <QTranslator>
#include <QSettings>
#include <fstream>
#include <QDesktopWidget>
#include <QProcess>
#include <QSurfaceFormat> 

#include <pthread.h>

#include "windows.h"
#include "iostream"
#include "string"

#include "DetuPVMS.h"
#include "dump.h"

#include "DetuPVMSIni.h"

#include "zlib.h"
#include "quazip/JlCompress.h"

using namespace std;

int main(int argc, char *argv[]){

	EnableAutoDump();
    QApplication a(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
	QSurfaceFormat fmt;
	fmt.setSamples(16);
	fmt.setDepthBufferSize(24);
	QSurfaceFormat::setDefaultFormat(fmt);

    //设置窗口最小大小，显示屏幕的四分之三
    QDesktopWidget* current_desktop = a.desktop();
    QRect rect = current_desktop->availableGeometry();
    rect.setWidth(rect.width() * 3 / 4);
    rect.setHeight(rect.height() * 3 / 4);
	QTranslator DetuPVMS_translator;

	QDir dir;
	QString initFilePath = QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/");

	if (!dir.exists(initFilePath + "/pts"))
	{
		if (!dir.mkpath(initFilePath + "/pts"))
		{
			return -1;
		}
	}
	
	if (!dir.exists(initFilePath + "/flv"))
	{
		if (!dir.mkpath(initFilePath + "/flv"))
		{
			return -1;
		}
	}

	if (!dir.exists(initFilePath + "/Map/panoMap"))
	{
		if (!dir.mkpath(initFilePath + "/Map/panoMap"))
		{
			return -1;
		}
	}

	JlCompress::compressDir(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS") + "/Map.zip", QDir::cleanPath(QApplication::applicationDirPath()+ "/Map")); //压缩
	JlCompress::extractDir(QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS") + "/Map.zip", QDir::cleanPath(QDir::homePath() + "/AppData/Local/Pano-VMS/Map"));//解压缩  


	if (!dir.exists(initFilePath + "/flv/REPLAY"))
	{
		if (!dir.mkpath(initFilePath + "/flv/REPLAY"))
		{
			return -1;
		}
	}

	if (!dir.exists(initFilePath))
	{
		if (!dir.mkpath(initFilePath))
		{
			return -1;
		}
	}

	if (!dir.exists(initFilePath + "/log"))
	{
		if (!dir.mkpath(initFilePath + "/log"))
		{
			return -1;
		}
	}

	QString log_name = "/log.txt";
	QString log_path = initFilePath + "/log" + log_name;
	std::string logpath = log_path.toLocal8Bit().data();
	Log::Initialise(logpath);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	dir.mkdir(initFilePath + "/Dump");

	initFilePath.append("/Pano-VMS.ini");
	if (!dir.exists(initFilePath))
	{
		std::ofstream init_file(initFilePath.toLocal8Bit());
	}

	//语言
	QSettings ini_reader(initFilePath, QSettings::IniFormat);
	QString locale = ini_reader.value("/locale").toString();
	if (locale.isEmpty())
	{
		locale = QLocale::system().name();
		ini_reader.setValue("/locale", locale);
	}

	if (locale == "zh_CN")
	{
		QLocale locale("zh_CN");
		QLocale::setDefault(locale);

		QString path = QApplication::applicationDirPath() + "/detupvms_zh.qm";
		DetuPVMS_translator.load(path);
		a.installTranslator(&DetuPVMS_translator);

	}
	else if (locale == "en_US")
	{
		QLocale locale("en_US");
		QLocale::setDefault(locale);
	}

	a.setProperty("local", locale);
    DetuPVMS w;
    w.hide();
    w.setWindowState(Qt::WindowFullScreen);
    w.setWindowState(Qt::WindowNoState);

    return a.exec();
}
