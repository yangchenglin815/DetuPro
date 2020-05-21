/********************************************************************************
** Form generated from reading UI file 'consoleWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLEWGT_H
#define UI_CONSOLEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "commonpagewgt.h"

QT_BEGIN_NAMESPACE

class Ui_consoleWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    commonPageWgt *playPage_;
    commonPageWgt *replayPage_;
    commonPageWgt *devicePage_;
    commonPageWgt *storagePage_;
    commonPageWgt *VRMapPage;
    commonPageWgt *VRViewPage;
    commonPageWgt *IOTPage_;

    void setupUi(QWidget *consoleWgt)
    {
        if (consoleWgt->objectName().isEmpty())
            consoleWgt->setObjectName(QStringLiteral("consoleWgt"));
        consoleWgt->resize(1218, 688);
        consoleWgt->setMinimumSize(QSize(0, 0));
        consoleWgt->setStyleSheet(QLatin1String("#consoleWgt{\n"
"background:#1f2020;\n"
"}"));
        horizontalLayout = new QHBoxLayout(consoleWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(consoleWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"}"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        playPage_ = new commonPageWgt(widget);
        playPage_->setObjectName(QStringLiteral("playPage_"));
        playPage_->setMinimumSize(QSize(325, 126));
        playPage_->setMaximumSize(QSize(325, 126));
        playPage_->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(playPage_, 0, 0, 1, 1);

        replayPage_ = new commonPageWgt(widget);
        replayPage_->setObjectName(QStringLiteral("replayPage_"));
        replayPage_->setMinimumSize(QSize(325, 126));
        replayPage_->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(replayPage_, 0, 1, 1, 1);

        devicePage_ = new commonPageWgt(widget);
        devicePage_->setObjectName(QStringLiteral("devicePage_"));
        devicePage_->setMinimumSize(QSize(325, 126));
        devicePage_->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(devicePage_, 1, 0, 1, 1);

        storagePage_ = new commonPageWgt(widget);
        storagePage_->setObjectName(QStringLiteral("storagePage_"));
        storagePage_->setMinimumSize(QSize(325, 126));
        storagePage_->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(storagePage_, 1, 1, 1, 1);

        VRMapPage = new commonPageWgt(widget);
        VRMapPage->setObjectName(QStringLiteral("VRMapPage"));
        VRMapPage->setMinimumSize(QSize(325, 126));
        VRMapPage->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(VRMapPage, 2, 0, 1, 1);

        VRViewPage = new commonPageWgt(widget);
        VRViewPage->setObjectName(QStringLiteral("VRViewPage"));
        VRViewPage->setMinimumSize(QSize(325, 126));
        VRViewPage->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(VRViewPage, 2, 1, 1, 1);

        IOTPage_ = new commonPageWgt(widget);
        IOTPage_->setObjectName(QStringLiteral("IOTPage_"));
        IOTPage_->setMinimumSize(QSize(325, 126));
        IOTPage_->setMaximumSize(QSize(325, 126));

        gridLayout->addWidget(IOTPage_, 3, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(consoleWgt);

        QMetaObject::connectSlotsByName(consoleWgt);
    } // setupUi

    void retranslateUi(QWidget *consoleWgt)
    {
        consoleWgt->setWindowTitle(QApplication::translate("consoleWgt", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class consoleWgt: public Ui_consoleWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLEWGT_H
