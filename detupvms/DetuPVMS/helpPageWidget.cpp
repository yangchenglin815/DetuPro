#include "helpPageWidget.h"

HelpPageWidget::HelpPageWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	initConnect();
}

HelpPageWidget::~HelpPageWidget()
{

}

void HelpPageWidget::leaveEvent(QEvent *event)
{
	setCursor(Qt::ArrowCursor);
}

void HelpPageWidget::enterEvent(QEvent *event)
{
	setCursor(Qt::PointingHandCursor);
}

void HelpPageWidget::initConnect()
{
	connect(ui.aboutBtn, SIGNAL(clicked()), this, SIGNAL(sigOnclickToAboutBtn()));
	connect(ui.helpBtn, SIGNAL(clicked()), this, SIGNAL(sigOnclickToHelpBtn()));
	//connect(ui.feedbackBtn, SIGNAL(clicked()), this, SIGNAL(sigOnclickToFeedbackBtn()));
}
