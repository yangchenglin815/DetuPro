/************************************************
* \file directionArrowWgt.h
*
* \author HuZhengdong
* \date 20171214
* 场景切换提示窗口，正在加载中
************************************************/
#ifndef SEQUENCERTIPWGT_H
#define SEQUENCERTIPWGT_H

#include <QWidget>
#include "ui_SequencerTipWgt.h"

class SequencerTipWgt : public QWidget
{
	Q_OBJECT

public:
	SequencerTipWgt(QWidget *parent = 0);
	~SequencerTipWgt();

	void setGif(QString gif_path);

private:
	Ui::SequencerTipWgt ui;
};

#endif // SEQUENCERTIPWGT_H
