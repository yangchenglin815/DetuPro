#include "cmdtest.h"
#include <QtWidgets/QApplication>
#include "logging.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	std::string url = "cmdtest.log";
	Log::Initialise(url);
	Log::SetThreshold(Log::LOG_TYPE_DEBUG);

	CmdTEST w;
	w.show();
	return a.exec();
}
