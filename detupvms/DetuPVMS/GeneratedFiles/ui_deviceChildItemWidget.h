/********************************************************************************
** Form generated from reading UI file 'deviceChildItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICECHILDITEMWIDGET_H
#define UI_DEVICECHILDITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "linewidget.h"

QT_BEGIN_NAMESPACE

class Ui_deviceChildItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    lineWidget *widget;
    QLabel *deviceLabel;

    void setupUi(QWidget *deviceChildItemWidget)
    {
        if (deviceChildItemWidget->objectName().isEmpty())
            deviceChildItemWidget->setObjectName(QStringLiteral("deviceChildItemWidget"));
        deviceChildItemWidget->resize(139, 30);
        deviceChildItemWidget->setMinimumSize(QSize(0, 30));
        deviceChildItemWidget->setMaximumSize(QSize(16777215, 30));
        deviceChildItemWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#cccccc;\n"
"}"));
        horizontalLayout = new QHBoxLayout(deviceChildItemWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 0, -1, 0);
        widget = new lineWidget(deviceChildItemWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(6, 0));
        widget->setMaximumSize(QSize(6, 16777215));

        horizontalLayout->addWidget(widget);

        deviceLabel = new QLabel(deviceChildItemWidget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));

        horizontalLayout->addWidget(deviceLabel);


        retranslateUi(deviceChildItemWidget);

        QMetaObject::connectSlotsByName(deviceChildItemWidget);
    } // setupUi

    void retranslateUi(QWidget *deviceChildItemWidget)
    {
        deviceChildItemWidget->setWindowTitle(QApplication::translate("deviceChildItemWidget", "Form", 0));
        deviceLabel->setText(QApplication::translate("deviceChildItemWidget", "\347\220\203\346\234\272A", 0));
    } // retranslateUi

};

namespace Ui {
    class deviceChildItemWidget: public Ui_deviceChildItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICECHILDITEMWIDGET_H
