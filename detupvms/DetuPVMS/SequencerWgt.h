/************************************************
* \file SequencerWgt.h
*
* \author HuZhengdong 
* \date 20171206
* ȫ�������л�
************************************************/
#ifndef SEQUENCERWGT_H
#define SEQUENCERWGT_H

#include <QWidget>
#include "ui_SequencerWgt.h"

class SequencerWgt : public QWidget
{
	Q_OBJECT

public:
	SequencerWgt(QWidget *parent = 0);
	~SequencerWgt();

private:
	Ui::SequencerWgt ui;
};

#endif // SEQUENCERWGT_H
