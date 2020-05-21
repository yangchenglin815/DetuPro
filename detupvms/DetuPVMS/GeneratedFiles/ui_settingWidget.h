/********************************************************************************
** Form generated from reading UI file 'settingWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

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
#include <QtWidgets/QWidget>
#include "commonlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_settingWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    commonLineEdit *deviceName;
    QLabel *label_2;
    QWidget *imageWidget;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QPushButton *autoBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *settingWidget)
    {
        if (settingWidget->objectName().isEmpty())
            settingWidget->setObjectName(QStringLiteral("settingWidget"));
        settingWidget->resize(521, 314);
        settingWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"QWidget#widget{\n"
"background:#eeeeee;\n"
"box-shadow:0 2px 10px 1px rgba(0,0,0,0.20);\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(settingWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(settingWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(90, 20, 100, 40);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(14);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(48, 12));
        label->setMaximumSize(QSize(48, 12));
        label->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        deviceName = new commonLineEdit(widget);
        deviceName->setObjectName(QStringLiteral("deviceName"));
        deviceName->setMinimumSize(QSize(220, 29));

        gridLayout->addWidget(deviceName, 0, 1, 1, 3);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(48, 12));
        label_2->setMaximumSize(QSize(48, 12));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        imageWidget = new QWidget(widget);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setMinimumSize(QSize(220, 110));

        gridLayout->addWidget(imageWidget, 1, 1, 2, 3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(48, 12));
        label_3->setMaximumSize(QSize(48, 12));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        autoBtn = new QPushButton(widget);
        autoBtn->setObjectName(QStringLiteral("autoBtn"));
        autoBtn->setMinimumSize(QSize(30, 14));
        autoBtn->setMaximumSize(QSize(30, 14));
        autoBtn->setStyleSheet(QStringLiteral("border-image:url(:/image/image/effects.png);"));

        gridLayout->addWidget(autoBtn, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        cancelBtn = new QPushButton(widget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QString::fromUtf8("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""));

        gridLayout->addWidget(cancelBtn, 4, 1, 1, 1);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QString::fromUtf8("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"width:80px;\n"
"height:26px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(confirmBtn, 4, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 3, 1, 1);


        horizontalLayout_2->addLayout(gridLayout);


        horizontalLayout->addWidget(widget);


        retranslateUi(settingWidget);

        QMetaObject::connectSlotsByName(settingWidget);
    } // setupUi

    void retranslateUi(QWidget *settingWidget)
    {
        settingWidget->setWindowTitle(QApplication::translate("settingWidget", "Form", 0));
        label->setText(QApplication::translate("settingWidget", "\350\256\276\345\244\207\345\210\253\345\220\215", 0));
        label_2->setText(QApplication::translate("settingWidget", "\351\242\204\347\275\256\347\224\273\351\235\242", 0));
        label_3->setText(QApplication::translate("settingWidget", "\350\207\252\345\212\250\346\227\213\350\275\254", 0));
        autoBtn->setText(QString());
        cancelBtn->setText(QApplication::translate("settingWidget", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("settingWidget", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class settingWidget: public Ui_settingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
