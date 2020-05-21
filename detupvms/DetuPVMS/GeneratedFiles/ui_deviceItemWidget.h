/********************************************************************************
** Form generated from reading UI file 'deviceItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEITEMWIDGET_H
#define UI_DEVICEITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deviceItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *iconLabel;
    QLabel *deviceLabel;
    QLabel *stateLabel;

    void setupUi(QWidget *deviceItemWidget)
    {
        if (deviceItemWidget->objectName().isEmpty())
            deviceItemWidget->setObjectName(QStringLiteral("deviceItemWidget"));
        deviceItemWidget->resize(190, 30);
        deviceItemWidget->setMinimumSize(QSize(190, 30));
        deviceItemWidget->setMaximumSize(QSize(190, 30));
        deviceItemWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(deviceItemWidget);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 0, 20, 0);
        iconLabel = new QLabel(deviceItemWidget);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setMinimumSize(QSize(8, 8));
        iconLabel->setMaximumSize(QSize(8, 8));
        iconLabel->setStyleSheet(QLatin1String("background:yellow;\n"
"border-radius:4px;"));

        horizontalLayout->addWidget(iconLabel);

        deviceLabel = new QLabel(deviceItemWidget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        deviceLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#CCCCCC;"));

        horizontalLayout->addWidget(deviceLabel, 0, Qt::AlignLeft);

        stateLabel = new QLabel(deviceItemWidget);
        stateLabel->setObjectName(QStringLiteral("stateLabel"));
        stateLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:yellow;"));

        horizontalLayout->addWidget(stateLabel, 0, Qt::AlignRight);


        retranslateUi(deviceItemWidget);

        QMetaObject::connectSlotsByName(deviceItemWidget);
    } // setupUi

    void retranslateUi(QWidget *deviceItemWidget)
    {
        deviceItemWidget->setWindowTitle(QApplication::translate("deviceItemWidget", "Form", 0));
        iconLabel->setText(QString());
        deviceLabel->setText(QApplication::translate("deviceItemWidget", "\350\256\276\345\244\207A", 0));
        stateLabel->setText(QApplication::translate("deviceItemWidget", "\345\267\262\345\212\240\350\275\275", 0));
    } // retranslateUi

};

namespace Ui {
    class deviceItemWidget: public Ui_deviceItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEITEMWIDGET_H
