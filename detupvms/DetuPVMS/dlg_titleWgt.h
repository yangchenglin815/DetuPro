/************************************************
* \file dlg_titleWgt.h
*
* \author HuZhengdong && YangChenglin
* \date 20170721
* µ¯¿ò±êÌâÀ¸
************************************************/
#ifndef DLG_TITLEWGT_H
#define DLG_TITLEWGT_H

#include <QWidget>

namespace Ui {
class dlg_titleWgt;
}

class dlg_titleWgt : public QWidget
{
    Q_OBJECT

public:
    explicit dlg_titleWgt(QWidget *parent = 0);
    ~dlg_titleWgt();
    void setLabelText(QString str);
	void setHideCloseBtn(bool isHidden);
signals:
    void sigonClose();
private:
    void initConnect();
private:
    Ui::dlg_titleWgt *ui;
};

#endif // DLG_TITLEWGT_H
