#ifndef DEVICECHILDITEMWIDGET_H
#define DEVICECHILDITEMWIDGET_H

#include <QWidget>

namespace Ui {
class deviceChildItemWidget;
}

class deviceChildItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit deviceChildItemWidget(QWidget *parent = 0);
    ~deviceChildItemWidget();
    void setIsFinal(bool isFinal);
	void setLabelText(QString text);
private:
    Ui::deviceChildItemWidget *ui;
};

#endif // DEVICECHILDITEMWIDGET_H
