#include <QMovie>
#include <QGraphicsOpacityEffect>

#include "SequencerTipWgt.h"

SequencerTipWgt::SequencerTipWgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint);

	QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
	setGraphicsEffect(opacityEffect);
	opacityEffect->setOpacity(0.9);
	
}

SequencerTipWgt::~SequencerTipWgt()
{

}

void SequencerTipWgt::setGif(QString gif_path)
{
	QMovie *movie = new QMovie(gif_path);
	QSize gif(29, 29);
	movie->setScaledSize(gif);
	ui.gif_label_->setMovie(movie);
	movie->start();
}
