#include "tscuter.h"
#include <QtWidgets/QApplication>
#include "logging.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	std::string url = "cuter.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	TsCuter w;
	w.show();
	return a.exec();
}
