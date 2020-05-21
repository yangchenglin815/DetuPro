#ifndef PICTUREGROUPWGT_H
#define PICTUREGROUPWGT_H

#pragma once
#pragma execution_character_set("utf-8")

#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>

#include "constStruct.h"

namespace Ui {
class pictureGroupWgt;
}

class pictureGroupWgt : public QWidget
{
    Q_OBJECT

public:
    explicit pictureGroupWgt(QWidget *parent = 0);
     ~pictureGroupWgt();
    void maskUI(QSize picSize, int space, bool isGird, PanoSceneInfo sceneInfo);
signals:
	void sigOnHiddenPicGroup();
private slots:
    void slotOnButtonClicked(int row);
	void slotOnCloseClicked();
private:
    Ui::pictureGroupWgt *ui;
	QMap<int, PanoSceneInfo> m_itemUrl;
};

#endif // PICTUREGROUPWGT_H
