/********************************************************************************
** Form generated from reading UI file 'VRViewWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRVIEWWIDGET_H
#define UI_VRVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "MapWgt.h"

QT_BEGIN_NAMESPACE

class Ui_VRViewWidget
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *initPage;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QPushButton *arrowButton;
    QSpacerItem *horizontalSpacer_2;
    MapWgt *mapPage;

    void setupUi(QWidget *VRViewWidget)
    {
        if (VRViewWidget->objectName().isEmpty())
            VRViewWidget->setObjectName(QStringLiteral("VRViewWidget"));
        VRViewWidget->resize(1077, 625);
        VRViewWidget->setStyleSheet(QString::fromUtf8("#initPage{\n"
"background-color:#1f2020;\n"
"}\n"
"#mapPage{\n"
"background:transparent;\n"
"}\n"
"#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgba(238,238,238,1);\n"
"line-height:17px;\n"
"}\n"
"#arrowButton{\n"
"border-image:url(:/image/image/nextArrow.png);\n"
"}\n"
"#arrowButton:hover{\n"
"border-image:url(:/image/image/nextArrowh.png);\n"
"}"));
        gridLayout = new QGridLayout(VRViewWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(VRViewWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        initPage = new QWidget();
        initPage->setObjectName(QStringLiteral("initPage"));
        gridLayout_2 = new QGridLayout(initPage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 246, -1, 300);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(initPage);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(208, 17));
        label->setMaximumSize(QSize(208, 17));

        horizontalLayout->addWidget(label);

        arrowButton = new QPushButton(initPage);
        arrowButton->setObjectName(QStringLiteral("arrowButton"));
        arrowButton->setMinimumSize(QSize(28, 28));
        arrowButton->setMaximumSize(QSize(28, 28));

        horizontalLayout->addWidget(arrowButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        stackedWidget->addWidget(initPage);
        mapPage = new MapWgt();
        mapPage->setObjectName(QStringLiteral("mapPage"));
        stackedWidget->addWidget(mapPage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(VRViewWidget);

        QMetaObject::connectSlotsByName(VRViewWidget);
    } // setupUi

    void retranslateUi(QWidget *VRViewWidget)
    {
        VRViewWidget->setWindowTitle(QApplication::translate("VRViewWidget", "VRViewWidget", 0));
        label->setText(QApplication::translate("VRViewWidget", "\350\257\267\345\205\210\345\234\250\345\257\274\350\247\210\350\256\276\347\275\256\344\270\255\346\267\273\345\212\240\345\234\260\345\233\276\344\270\216\345\205\250\346\231\257\346\234\272", 0));
        arrowButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VRViewWidget: public Ui_VRViewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRVIEWWIDGET_H
