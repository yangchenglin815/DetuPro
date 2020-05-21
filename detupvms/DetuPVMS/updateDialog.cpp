#include "updateDialog.h"

updateDialog::updateDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	connect(ui.confirmBtn, SIGNAL(clicked()), this, SLOT(accept()));
	connect(ui.cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
}

updateDialog::~updateDialog()
{

}
