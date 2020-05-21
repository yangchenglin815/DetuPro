#include "iotwgt.h"

IOTWgt::IOTWgt(QWidget *parent)
	: QWidget(parent), m_platform_view(NULL)
{
	ui.setupUi(this);

 //	m_platform_view = new QWebEngineView(this);
//  	m_platform_view->load(QUrl("http://case.detuyun.com/m1/#/pages/login"));
// 	m_platform_view->show();
}

IOTWgt::~IOTWgt()
{
// 	m_platform_view->stop();
// 	m_platform_view->deleteLater();
// 	m_platform_view = NULL;
}

void IOTWgt::resizeEvent(QResizeEvent *event)
{
	if (m_platform_view != NULL)
	{
		m_platform_view->resize(this->size());
	}
	return QWidget::resizeEvent(event);
}
