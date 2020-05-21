#include "SequencerWgt.h"

SequencerWgt::SequencerWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);
}

SequencerWgt::~SequencerWgt()
{

}
