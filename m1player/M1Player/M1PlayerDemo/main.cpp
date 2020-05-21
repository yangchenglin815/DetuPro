#include "m1playerdemo.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include "logging.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QSurfaceFormat fmt;
	fmt.setSamples(16);
	fmt.setDepthBufferSize(24);
	QSurfaceFormat::setDefaultFormat(fmt);

	std::string url = "M1PlayerDemo.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	QtM1PlayerDemo w;
	w.show();
	return a.exec();
}
