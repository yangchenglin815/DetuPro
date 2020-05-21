#include "storageTitleWgt.h"
#include <QPainter>

storageTitleWgt::storageTitleWgt(QWidget *parent)
	: QWidget(parent)
{

}

storageTitleWgt::~storageTitleWgt()
{

}

void storageTitleWgt::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	painter.fillRect(this->rect(), QBrush("#1f2020"));

	const int m_nFontSize = 12;
	QFont font;
	font.setPixelSize(m_nFontSize);
	font.setFamily("΢���ź�");
	painter.setFont(font);
	QPen pen;
	pen.setColor("#868989");
	painter.setPen(pen);

	//�ܼ�5������
	static const int c_nFirstColWidth = 75;
	static const int c_nSecondColWidth = 120;
	static const int c_nThirdColWidth = 181;
	static const int c_nFourthColWidth = 179;
	static const int c_nFiveColWidth = 180;

	static const QString c_sFirstColTitle = QStringLiteral("���");
	static const QString c_sSecondColTitle = QStringLiteral("����");
	static const QString c_sThirdColTitle = QStringLiteral("�豸���к�");
	static const QString c_sFourthColTitle = QStringLiteral("���ÿռ�(GB)");
	static const QString c_sFiveColTitle = QStringLiteral("ʹ�ÿռ�(GB)");

	int nHeight = this->height();
	int xPos = 0;
	int yPos = 0;
	//
	QRect textRect1(xPos, yPos, c_nFirstColWidth, nHeight);
	painter.drawText(textRect1, Qt::AlignRight | Qt::AlignVCenter, c_sFirstColTitle);

	//
	xPos += c_nFirstColWidth;
	QRect textRect2(xPos, yPos, c_nSecondColWidth, nHeight);
	painter.drawText(textRect2, Qt::AlignRight | Qt::AlignVCenter, c_sSecondColTitle);

	//
	xPos += c_nSecondColWidth;
	QRect textRect3(xPos, yPos, c_nThirdColWidth, nHeight);
	painter.drawText(textRect3, Qt::AlignRight | Qt::AlignVCenter, c_sThirdColTitle);

	//
	xPos += c_nThirdColWidth;
	QRect textRect4(xPos, yPos, c_nFourthColWidth, nHeight);
	painter.drawText(textRect4, Qt::AlignRight | Qt::AlignVCenter, c_sFourthColTitle);

	xPos += c_nFourthColWidth;
	QRect textRect5(xPos, yPos, c_nFiveColWidth, nHeight);
	painter.drawText(textRect5, Qt::AlignRight | Qt::AlignVCenter, c_sFiveColTitle);

	pen.setColor("#444444");
	pen.setWidth(3);
	painter.setPen(pen);
	painter.drawLine(0, nHeight - 1, this->width(), nHeight - 1);
}
