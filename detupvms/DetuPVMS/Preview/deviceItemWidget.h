#ifndef DEVICEITEMWIDGET_H
#define DEVICEITEMWIDGET_H

#include <QWidget>
#include "../constStruct.h"

namespace Ui {
class deviceItemWidget;
}

class deviceItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit deviceItemWidget(QWidget *parent = 0);
    ~deviceItemWidget();
	void initData(deviceInfo pvsList, int type);
private:
    Ui::deviceItemWidget *ui;
};

#endif // DEVICEITEMWIDGET_H
