/********************************************************************************
** Form generated from reading UI file 'homeWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEWGT_H
#define UI_HOMEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "VRMap/VRMapWidget.h"
#include "VRView/VRViewWidget.h"
#include "consoletabwidget.h"
#include "consolewgt.h"
#include "devicemanagewgt.h"
#include "iotwgt.h"
#include "playwidget.h"
#include "replaywgt.h"
#include "storagewgt.h"
#include "suptabwidget.h"

QT_BEGIN_NAMESPACE

class Ui_homeWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *contrlWgt;
    QHBoxLayout *horizontalLayout_2;
    consoleTabWidget *tabConsoleWgt_;
    supTabWidget *tabPlayWgt_;
    supTabWidget *tabReplayWgt_;
    supTabWidget *tabDeviceWgt_;
    supTabWidget *tabStorageWgt_;
    supTabWidget *tabVRMapWgt_;
    supTabWidget *tabVRViewWgt_;
    supTabWidget *tabIOTPlatformWgt_;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    consoleWgt *consoleWgt_;
    deviceManageWgt *deviceWgt_;
    playWidget *playWgt_;
    replayWgt *replayWgt_;
    storageWgt *storageWgt_;
    VRMapWidget *VRMapWgt_;
    VRViewWidget *VRViewWgt_;
    IOTWgt *IOTPlatWgt_;

    void setupUi(QWidget *homeWgt)
    {
        if (homeWgt->objectName().isEmpty())
            homeWgt->setObjectName(QStringLiteral("homeWgt"));
        homeWgt->resize(1200, 595);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(homeWgt->sizePolicy().hasHeightForWidth());
        homeWgt->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(homeWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(homeWgt);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        contrlWgt = new QWidget(widget);
        contrlWgt->setObjectName(QStringLiteral("contrlWgt"));
        contrlWgt->setMinimumSize(QSize(0, 30));
        contrlWgt->setMaximumSize(QSize(16777215, 30));
        contrlWgt->setStyleSheet(QLatin1String("#contrlWgt{\n"
"background:#2a2b2b;\n"
"border:1px solid #000000;\n"
"border-left:none;\n"
"border-right:none;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(contrlWgt);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tabConsoleWgt_ = new consoleTabWidget(contrlWgt);
        tabConsoleWgt_->setObjectName(QStringLiteral("tabConsoleWgt_"));
        sizePolicy.setHeightForWidth(tabConsoleWgt_->sizePolicy().hasHeightForWidth());
        tabConsoleWgt_->setSizePolicy(sizePolicy);
        tabConsoleWgt_->setMinimumSize(QSize(96, 0));
        tabConsoleWgt_->setMaximumSize(QSize(96, 16777215));
        tabConsoleWgt_->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(tabConsoleWgt_);

        tabPlayWgt_ = new supTabWidget(contrlWgt);
        tabPlayWgt_->setObjectName(QStringLiteral("tabPlayWgt_"));
        sizePolicy.setHeightForWidth(tabPlayWgt_->sizePolicy().hasHeightForWidth());
        tabPlayWgt_->setSizePolicy(sizePolicy);
        tabPlayWgt_->setMinimumSize(QSize(96, 0));
        tabPlayWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabPlayWgt_);

        tabReplayWgt_ = new supTabWidget(contrlWgt);
        tabReplayWgt_->setObjectName(QStringLiteral("tabReplayWgt_"));
        sizePolicy.setHeightForWidth(tabReplayWgt_->sizePolicy().hasHeightForWidth());
        tabReplayWgt_->setSizePolicy(sizePolicy);
        tabReplayWgt_->setMinimumSize(QSize(96, 0));
        tabReplayWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabReplayWgt_);

        tabDeviceWgt_ = new supTabWidget(contrlWgt);
        tabDeviceWgt_->setObjectName(QStringLiteral("tabDeviceWgt_"));
        sizePolicy.setHeightForWidth(tabDeviceWgt_->sizePolicy().hasHeightForWidth());
        tabDeviceWgt_->setSizePolicy(sizePolicy);
        tabDeviceWgt_->setMinimumSize(QSize(96, 0));
        tabDeviceWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabDeviceWgt_);

        tabStorageWgt_ = new supTabWidget(contrlWgt);
        tabStorageWgt_->setObjectName(QStringLiteral("tabStorageWgt_"));
        sizePolicy.setHeightForWidth(tabStorageWgt_->sizePolicy().hasHeightForWidth());
        tabStorageWgt_->setSizePolicy(sizePolicy);
        tabStorageWgt_->setMinimumSize(QSize(96, 0));
        tabStorageWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabStorageWgt_);

        tabVRMapWgt_ = new supTabWidget(contrlWgt);
        tabVRMapWgt_->setObjectName(QStringLiteral("tabVRMapWgt_"));
        tabVRMapWgt_->setMinimumSize(QSize(96, 0));
        tabVRMapWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabVRMapWgt_);

        tabVRViewWgt_ = new supTabWidget(contrlWgt);
        tabVRViewWgt_->setObjectName(QStringLiteral("tabVRViewWgt_"));
        tabVRViewWgt_->setMinimumSize(QSize(96, 0));
        tabVRViewWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabVRViewWgt_);

        tabIOTPlatformWgt_ = new supTabWidget(contrlWgt);
        tabIOTPlatformWgt_->setObjectName(QStringLiteral("tabIOTPlatformWgt_"));
        tabIOTPlatformWgt_->setMinimumSize(QSize(96, 0));
        tabIOTPlatformWgt_->setMaximumSize(QSize(96, 16777215));

        horizontalLayout_2->addWidget(tabIOTPlatformWgt_);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(contrlWgt);

        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        consoleWgt_ = new consoleWgt();
        consoleWgt_->setObjectName(QStringLiteral("consoleWgt_"));
        stackedWidget->addWidget(consoleWgt_);
        deviceWgt_ = new deviceManageWgt();
        deviceWgt_->setObjectName(QStringLiteral("deviceWgt_"));
        stackedWidget->addWidget(deviceWgt_);
        playWgt_ = new playWidget();
        playWgt_->setObjectName(QStringLiteral("playWgt_"));
        stackedWidget->addWidget(playWgt_);
        replayWgt_ = new replayWgt();
        replayWgt_->setObjectName(QStringLiteral("replayWgt_"));
        stackedWidget->addWidget(replayWgt_);
        storageWgt_ = new storageWgt();
        storageWgt_->setObjectName(QStringLiteral("storageWgt_"));
        stackedWidget->addWidget(storageWgt_);
        VRMapWgt_ = new VRMapWidget();
        VRMapWgt_->setObjectName(QStringLiteral("VRMapWgt_"));
        stackedWidget->addWidget(VRMapWgt_);
        VRViewWgt_ = new VRViewWidget();
        VRViewWgt_->setObjectName(QStringLiteral("VRViewWgt_"));
        stackedWidget->addWidget(VRViewWgt_);
        IOTPlatWgt_ = new IOTWgt();
        IOTPlatWgt_->setObjectName(QStringLiteral("IOTPlatWgt_"));
        stackedWidget->addWidget(IOTPlatWgt_);

        verticalLayout->addWidget(stackedWidget);


        horizontalLayout->addWidget(widget);


        retranslateUi(homeWgt);

        QMetaObject::connectSlotsByName(homeWgt);
    } // setupUi

    void retranslateUi(QWidget *homeWgt)
    {
        homeWgt->setWindowTitle(QApplication::translate("homeWgt", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class homeWgt: public Ui_homeWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEWGT_H
