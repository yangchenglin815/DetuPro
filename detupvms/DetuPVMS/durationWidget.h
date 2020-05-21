#ifndef DURATIONWIDGET_H
#define DURATIONWIDGET_H

#include <QWidget>

namespace Ui {
class durationWidget;
}

class durationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit durationWidget(QWidget *parent = 0);
    ~durationWidget();
	int getDurationBySlider();
	void resetDuration();
signals:
    void sigOnValueChanged(int value);
public slots:
    void slotOnAddDuration();
    void slotOnDecreaseDuration();
    void slotOnValueChanged(int value);
private:
    void init();
    void initConnect();
private:
    Ui::durationWidget *ui;
};

#endif // DURATIONWIDGET_H
