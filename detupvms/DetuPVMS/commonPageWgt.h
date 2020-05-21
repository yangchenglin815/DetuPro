/************************************************
* \file commonPageWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* ����̨���ڶ��Ƶİ�ť
************************************************/
#ifndef COMMONPAGEWGT_H
#define COMMONPAGEWGT_H

#include <QWidget>

namespace Ui {
class commonPageWgt;
}

//����̨�ϵ�����ť
class commonPageWgt : public QWidget
{
    Q_OBJECT

public:

	enum ConsoleButton
	{
		Play = 0,
		RePlay,
		Device,
		Storage,
		VRMap,
		VRView,
		IOTPlat,
	};

    explicit commonPageWgt(QWidget *parent = 0);
    ~commonPageWgt();

	//����̨���ñ��������
	void setImageAndText(QString tittle, QString content, QString iconPath, commonPageWgt::ConsoleButton type);

protected:
	virtual void mousePressEvent(QMouseEvent *event);

signals:

	//����̨���水ť���������ڽ����ź�
	void TrigConsoleButtonClicked(commonPageWgt::ConsoleButton type);

private:
    Ui::commonPageWgt *ui;

	commonPageWgt::ConsoleButton type_;
};

#endif // COMMONPAGEWGT_H
