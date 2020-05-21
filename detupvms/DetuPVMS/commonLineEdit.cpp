#include "commonLineEdit.h"

commonLineEdit::commonLineEdit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initConnect();
	ui.pushButton->setFocusPolicy(Qt::NoFocus);
}

commonLineEdit::~commonLineEdit()
{

}

void commonLineEdit::setHintText(QString str)
{
	ui.lineEdit->setPlaceholderText(str);
}

void commonLineEdit::setMaxLength(int num)
{
	ui.lineEdit->setMaxLength(num);
}

void commonLineEdit::setValidator(QRegExpValidator* validator)
{
	ui.lineEdit->setValidator(validator);
}

void commonLineEdit::setText(QString str)
{
	ui.lineEdit->setText(str);
}

void commonLineEdit::setFocusLineEdit()
{
	ui.lineEdit->setFocus();
}

void commonLineEdit::setShowClose(bool isHidden)
{
	ui.pushButton->setHidden(isHidden);
}

QString commonLineEdit::getText()
{
	return ui.lineEdit->text();
}

void commonLineEdit::slot_clearText()
{
	ui.lineEdit->clear();
}

void commonLineEdit::initConnect()
{
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(slot_clearText()));
}
