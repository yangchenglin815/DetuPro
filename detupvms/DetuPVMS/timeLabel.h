#ifndef TIMELABEL_H
#define TIMELABEL_H

#include <QLabel>
#include <QPainter>
#include <QMouseEvent>

class timeLabel : public QLabel
{
    Q_OBJECT
public:
    explicit timeLabel(QWidget *parent = 0);
    void setShowTime(QString time);
protected:
    void paintEvent(QPaintEvent *event);
private:
    QString curr_time_;
};

#endif // TIMELABEL_H
