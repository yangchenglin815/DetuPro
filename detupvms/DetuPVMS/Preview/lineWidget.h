#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QWidget>

class lineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit lineWidget(QWidget *parent = 0);
    void setIsFinal(bool isFinal);
protected:
    void paintEvent(QPaintEvent *event);
private:
    bool m_isFinal;
};

#endif // LINEWIDGET_H
