#include "diskFormatDlg.h"

diskFormatDlg::diskFormatDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	init();
	initConnect();
}

diskFormatDlg::~diskFormatDlg()
{

}

void diskFormatDlg::initConnect()
{
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SIGNAL(sigOnDiskFormat()));
}

void diskFormatDlg::init()
{
	ui.titleWidget->setHideCloseBtn(true);
	ui.titleWidget->setLabelText(QStringLiteral("∏Ò ΩªØ"));
}
