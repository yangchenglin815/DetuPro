/********************************************************************************
** Form generated from reading UI file 'deviceManageWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEMANAGEWGT_H
#define UI_DEVICEMANAGEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "commonPushButton.h"
#include "devicemanagelistview.h"
#include "devicetittlewgt.h"
#include "ptzManageListView.h"
#include "spyManageListView.h"

QT_BEGIN_NAMESPACE

class Ui_deviceManageWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget *refreshWgt;
    QHBoxLayout *horizontalLayout_3;
    commonPushButton *toolButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    commonPushButton *panoramicBtn;
    commonPushButton *ptzBtn;
    commonPushButton *spyBtn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    deviceTittleWgt *tittleWgt;
    QStackedWidget *listStackedWidget;
    QWidget *homePage;
    QGridLayout *gridLayout_2;
    deviceManageListView *listView;
    QWidget *ptzPage;
    QGridLayout *gridLayout_3;
    ptzManageListView *ptzListView;
    QWidget *spyPage;
    QGridLayout *gridLayout_4;
    spyManageListView *spyListView;

    void setupUi(QWidget *deviceManageWgt)
    {
        if (deviceManageWgt->objectName().isEmpty())
            deviceManageWgt->setObjectName(QStringLiteral("deviceManageWgt"));
        deviceManageWgt->resize(1202, 650);
        deviceManageWgt->setStyleSheet(QLatin1String("QWidget#widget{\n"
"background:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"}"));
        horizontalLayout = new QHBoxLayout(deviceManageWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(deviceManageWgt);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(210, 36, 210, 20);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(5);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        refreshWgt = new QWidget(widget);
        refreshWgt->setObjectName(QStringLiteral("refreshWgt"));
        refreshWgt->setMinimumSize(QSize(780, 44));
        refreshWgt->setMaximumSize(QSize(16777215, 44));
        refreshWgt->setStyleSheet(QStringLiteral(""));
        horizontalLayout_3 = new QHBoxLayout(refreshWgt);
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, 9, 10);
        toolButton = new commonPushButton(refreshWgt);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(84, 28));
        toolButton->setMaximumSize(QSize(84, 28));
        toolButton->setLayoutDirection(Qt::LeftToRight);
        toolButton->setStyleSheet(QString::fromUtf8("#toolButton{\n"
"border:1px solid #868989;\n"
"border-radius:14px;\n"
"color:#868989;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"background-image:url(:/image/image/refresh.png);\n"
"border-size:26px 14px;\n"
"background-repeat:no-repeat; \n"
"background-position:left;\n"
"}\n"
"#toolButton:pressed{\n"
"padding-left:3px;\n"
"padding-top:3px;\n"
"}\n"
"#toolButton:hover{\n"
"border:1px solid #eeeeee;\n"
"color:#eeeeee;\n"
"background-image:url(:/image/image/refreshb.png);\n"
"}"));
        toolButton->setAutoRepeat(false);

        horizontalLayout_3->addWidget(toolButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        panoramicBtn = new commonPushButton(refreshWgt);
        panoramicBtn->setObjectName(QStringLiteral("panoramicBtn"));
        panoramicBtn->setMinimumSize(QSize(80, 30));
        panoramicBtn->setMaximumSize(QSize(80, 30));
        panoramicBtn->setStyleSheet(QString::fromUtf8("#panoramicBtn{\n"
"border:1px solid #444444;\n"
"border-right:none;\n"
"border-top-left-radius:14px;\n"
"border-bottom-left-radius:14px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#444444;\n"
"}\n"
"#panoramicBtn:checked{\n"
"color:#ffffff;\n"
"background:#444444;\n"
"}"));
        panoramicBtn->setCheckable(true);
        panoramicBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(panoramicBtn);

        ptzBtn = new commonPushButton(refreshWgt);
        ptzBtn->setObjectName(QStringLiteral("ptzBtn"));
        ptzBtn->setMinimumSize(QSize(80, 30));
        ptzBtn->setMaximumSize(QSize(80, 30));
        ptzBtn->setStyleSheet(QString::fromUtf8("#ptzBtn{\n"
"border:1px solid #444444;\n"
"border-right:none;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#444444;\n"
"}\n"
"#ptzBtn:checked{\n"
"color:#ffffff;\n"
"background:#444444;\n"
"}"));
        ptzBtn->setCheckable(true);
        ptzBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(ptzBtn);

        spyBtn = new commonPushButton(refreshWgt);
        spyBtn->setObjectName(QStringLiteral("spyBtn"));
        spyBtn->setMinimumSize(QSize(80, 30));
        spyBtn->setMaximumSize(QSize(80, 30));
        spyBtn->setStyleSheet(QString::fromUtf8("#spyBtn{\n"
"border:1px solid #444444;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border-top-right-radius:14px;\n"
"border-bottom-right-radius:14px;\n"
"font-size:12px;\n"
"color:#444444;\n"
"}\n"
"#spyBtn:checked{\n"
"color:#ffffff;\n"
"background:#444444;\n"
"}"));
        spyBtn->setCheckable(true);
        spyBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(spyBtn);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalSpacer_3 = new QSpacerItem(84, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addWidget(refreshWgt);

        tittleWgt = new deviceTittleWgt(widget);
        tittleWgt->setObjectName(QStringLiteral("tittleWgt"));
        tittleWgt->setMinimumSize(QSize(780, 44));
        tittleWgt->setMaximumSize(QSize(16777215, 44));

        verticalLayout->addWidget(tittleWgt);

        listStackedWidget = new QStackedWidget(widget);
        listStackedWidget->setObjectName(QStringLiteral("listStackedWidget"));
        listStackedWidget->setMinimumSize(QSize(780, 0));
        homePage = new QWidget();
        homePage->setObjectName(QStringLiteral("homePage"));
        gridLayout_2 = new QGridLayout(homePage);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        listView = new deviceManageListView(homePage);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setStyleSheet(QLatin1String("background:#1f2020;\n"
"border:none;"));

        gridLayout_2->addWidget(listView, 0, 0, 1, 1);

        listStackedWidget->addWidget(homePage);
        ptzPage = new QWidget();
        ptzPage->setObjectName(QStringLiteral("ptzPage"));
        gridLayout_3 = new QGridLayout(ptzPage);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        ptzListView = new ptzManageListView(ptzPage);
        ptzListView->setObjectName(QStringLiteral("ptzListView"));
        ptzListView->setStyleSheet(QLatin1String("background:#1f2020;\n"
"border:none;"));

        gridLayout_3->addWidget(ptzListView, 0, 0, 1, 1);

        listStackedWidget->addWidget(ptzPage);
        spyPage = new QWidget();
        spyPage->setObjectName(QStringLiteral("spyPage"));
        gridLayout_4 = new QGridLayout(spyPage);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        spyListView = new spyManageListView(spyPage);
        spyListView->setObjectName(QStringLiteral("spyListView"));
        spyListView->setStyleSheet(QLatin1String("background:#1f2020;\n"
"border:none;"));

        gridLayout_4->addWidget(spyListView, 0, 0, 1, 1);

        listStackedWidget->addWidget(spyPage);

        verticalLayout->addWidget(listStackedWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(deviceManageWgt);

        QMetaObject::connectSlotsByName(deviceManageWgt);
    } // setupUi

    void retranslateUi(QWidget *deviceManageWgt)
    {
        deviceManageWgt->setWindowTitle(QApplication::translate("deviceManageWgt", "Form", 0));
        toolButton->setText(QApplication::translate("deviceManageWgt", "     \345\210\267\346\226\260", 0));
        panoramicBtn->setText(QApplication::translate("deviceManageWgt", "\345\205\250\346\231\257\346\234\272", 0));
        ptzBtn->setText(QApplication::translate("deviceManageWgt", "\347\220\203\346\234\272", 0));
        spyBtn->setText(QApplication::translate("deviceManageWgt", "\346\236\252\346\234\272", 0));
    } // retranslateUi

};

namespace Ui {
    class deviceManageWgt: public Ui_deviceManageWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEMANAGEWGT_H
