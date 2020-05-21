#include "deviceTittleWgt.h"
#include "logging.hpp"


#include <QPainter>

deviceTittleWgt::deviceTittleWgt(QWidget *parent)
{
	m_currentIndex = 0;
}

deviceTittleWgt::~deviceTittleWgt()
{

}

void deviceTittleWgt::setCurrentPage(int index)
{
	m_currentIndex = index;	
	Log::Info("current page index : %d", m_currentIndex);
	update();
}

void deviceTittleWgt::paintHomePage(QPainter &painter, int nHeight)
{
	//�ܼ�5������
	static const int c_nFirstColWidth = 42;
	static const int c_nSecondColWidth = 100;
	static const int c_nThirdColWidth = 110;
	static const int c_nFourthColWidth = 150;
	static const int c_nFiveColWidth = 150;
	static const int c_nSixColWidth = 160;

	static const QString c_sFirstColTitle = QStringLiteral("���");
	static const QString c_sSecondColTitle = QStringLiteral("״̬");
	static const QString c_sThirdColTitle = QStringLiteral("����");
	static const QString c_sFourthColTitle = QStringLiteral("�豸���к�");
	static const QString c_sFiveColTitle = QStringLiteral("M1���к�");
	static const QString c_sSixColTitle = QStringLiteral("����");

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

	//
	xPos += c_nFourthColWidth;
	QRect textRect5(xPos, yPos, c_nFiveColWidth, nHeight);
	painter.drawText(textRect5, Qt::AlignRight | Qt::AlignVCenter, c_sFiveColTitle);

	//	
	xPos += c_nFiveColWidth;
	QRect textRect6(xPos, yPos, c_nSixColWidth, nHeight);
	painter.drawText(textRect6, Qt::AlignRight | Qt::AlignVCenter, c_sSixColTitle);

}

void deviceTittleWgt::paintPtzPage(QPainter &painter, int nHeight)
{
	static const int c_nFirstColWidth = 42;
	static const int c_nSecondColWidth = 210;
	static const int c_nThirdColWidth = 220;
	static const int c_nFourthColWidth = 230;

	static const QString c_sFirstColTitle = QStringLiteral("���");
	static const QString c_sSecondColTitle = QStringLiteral("IP��ַ");
	static const QString c_sThirdColTitle = QStringLiteral("�˿�");
	static const QString c_sFourthColTitle = QStringLiteral("����");

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
}

void deviceTittleWgt::paintEvent(QPaintEvent *event)
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
	int nHeight = this->height();

	switch (m_currentIndex)
	{
	case 0:
		paintHomePage(painter, nHeight);
		break;
	case 1:
	case 2:
		paintPtzPage(painter, nHeight);
		break;
	}
	pen.setColor("#444444");
	pen.setWidth(3);
	painter.setPen(pen);
	painter.drawLine(0, nHeight - 1, this->width(), nHeight - 1);
}
