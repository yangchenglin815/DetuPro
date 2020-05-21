/********************************************************************************
** Form generated from reading UI file 'mapToolWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPTOOLWIDGET_H
#define UI_MAPTOOLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <RFIDScreen.h>
#include "MinimapWgt.h"
#include "pictureGroupWgt.h"

QT_BEGIN_NAMESPACE

class Ui_mapToolWidget
{
public:
    QGridLayout *gridLayout_2;
    MinimapWgt *miniMapPage;
    RFIDScreen *rfidPage;
    pictureGroupWgt *pictureGroupPage;

    void setupUi(QWidget *mapToolWidget)
    {
        if (mapToolWidget->objectName().isEmpty())
            mapToolWidget->setObjectName(QStringLiteral("mapToolWidget"));
        mapToolWidget->resize(320, 647);
        mapToolWidget->setMinimumSize(QSize(320, 0));
        mapToolWidget->setMaximumSize(QSize(320, 16777215));
        gridLayout_2 = new QGridLayout(mapToolWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        miniMapPage = new MinimapWgt(mapToolWidget);
        miniMapPage->setObjectName(QStringLiteral("miniMapPage"));
        miniMapPage->setMinimumSize(QSize(0, 180));
        miniMapPage->setMaximumSize(QSize(16777215, 180));

        gridLayout_2->addWidget(miniMapPage, 0, 0, 1, 1);

        rfidPage = new RFIDScreen(mapToolWidget);
        rfidPage->setObjectName(QStringLiteral("rfidPage"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(rfidPage->sizePolicy().hasHeightForWidth());
        rfidPage->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(rfidPage, 1, 0, 1, 1);

        pictureGroupPage = new pictureGroupWgt(mapToolWidget);
        pictureGroupPage->setObjectName(QStringLiteral("pictureGroupPage"));
        sizePolicy.setHeightForWidth(pictureGroupPage->sizePolicy().hasHeightForWidth());
        pictureGroupPage->setSizePolicy(sizePolicy);
        pictureGroupPage->setMinimumSize(QSize(0, 0));
        pictureGroupPage->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(pictureGroupPage, 2, 0, 1, 1);


        retranslateUi(mapToolWidget);

        QMetaObject::connectSlotsByName(mapToolWidget);
    } // setupUi

    void retranslateUi(QWidget *mapToolWidget)
    {
        mapToolWidget->setWindowTitle(QApplication::translate("mapToolWidget", "mapToolWidget", 0));
    } // retranslateUi

};

namespace Ui {
    class mapToolWidget: public Ui_mapToolWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPTOOLWIDGET_H
