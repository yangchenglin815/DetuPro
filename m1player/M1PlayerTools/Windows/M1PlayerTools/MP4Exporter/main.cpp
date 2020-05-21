#include "mp4exporter.h"
#include <QtWidgets/QApplication>
#include "logging.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	std::string url = "mp4exporter.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	MP4Exporter w;
	w.show();
	return a.exec();
}
