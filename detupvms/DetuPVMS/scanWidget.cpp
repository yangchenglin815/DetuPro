#include <QFileDialog>

#include "scanWidget.h"

//全局控制器
#include "MessageManager.h"
#include "SocketManager.h"
#include "TcpDataManager.hpp"

using namespace dm::server;

scanWidget::scanWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

    connect(ui.keyboardButton, SIGNAL(clicked()), this, SLOT(SetCapturePath()));
}

scanWidget::~scanWidget()
{

}

void scanWidget::setUrlText(QString text)
{
	ui.searchLineEdit->setText(text);
	TcpDataManagerIns.setCapturePath(text);
}

void scanWidget::SetCapturePath()
{
	QString save_path = QFileDialog::getExistingDirectory(this, QStringLiteral("请选择存储目录"), QApplication::applicationDirPath());
    if (save_path.isEmpty())
    {
        return;
    }
    ui.searchLineEdit->setText(save_path);
    TcpDataManagerIns.setCapturePath(save_path);
}

