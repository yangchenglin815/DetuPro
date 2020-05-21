/********************************************************************************
** Form generated from reading UI file 'serverSettingWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSETTINGWGT_H
#define UI_SERVERSETTINGWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "qiplineedit.h"

QT_BEGIN_NAMESPACE

class Ui_serverSettingWgt
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QStackedWidget *stackedWidget;
    QWidget *settingsPage;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_2;
    QLineEdit *portLineEdit;
    QPushButton *cancelBtn;
    QIPLineEdit *ipLineEdit;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *warnLabel;
    QWidget *tipPage;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QPushButton *modifyBtn;
    QSpacerItem *verticalSpacer_2;
    QLabel *tipLabel;
    QPushButton *reconnectBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QWidget *progressPage;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *imageLabel;
    QLabel *hintLabel;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *serverSettingWgt)
    {
        if (serverSettingWgt->objectName().isEmpty())
            serverSettingWgt->setObjectName(QStringLiteral("serverSettingWgt"));
        serverSettingWgt->resize(524, 273);
        serverSettingWgt->setStyleSheet(QString::fromUtf8("#widget{\n"
"    \n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"QCheckBox{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(serverSettingWgt);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(serverSettingWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"    \n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        settingsPage = new QWidget();
        settingsPage->setObjectName(QStringLiteral("settingsPage"));
        settingsPage->setStyleSheet(QLatin1String("#settingsPage{\n"
"    \n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(settingsPage);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(90, 61, 130, 41);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(10);
        gridLayout_2->setVerticalSpacing(14);
        gridLayout_2->setContentsMargins(9, 9, 9, 9);
        portLineEdit = new QLineEdit(settingsPage);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setMinimumSize(QSize(206, 27));
        portLineEdit->setMaximumSize(QSize(206, 27));
        portLineEdit->setStyleSheet(QString::fromUtf8("#portLineEdit{\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:9px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"}"));
        portLineEdit->setClearButtonEnabled(false);

        gridLayout_2->addWidget(portLineEdit, 1, 1, 1, 2);

        cancelBtn = new QPushButton(settingsPage);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""));

        gridLayout_2->addWidget(cancelBtn, 6, 2, 1, 1);

        ipLineEdit = new QIPLineEdit(settingsPage);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(206, 27));
        ipLineEdit->setMaximumSize(QSize(206, 27));
        ipLineEdit->setStyleSheet(QString::fromUtf8("#ipLineEdit{\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"}\n"
"\n"
"QLineEdit{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"}\n"
""));
        ipLineEdit->setClearButtonEnabled(false);

        gridLayout_2->addWidget(ipLineEdit, 0, 1, 1, 2);

        confirmBtn = new QPushButton(settingsPage);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""));

        gridLayout_2->addWidget(confirmBtn, 6, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 6, 0, 1, 1);

        label = new QLabel(settingsPage);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(70, 0));
        label->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(settingsPage);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(70, 0));
        label_2->setMaximumSize(QSize(70, 16777215));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 1, 1, 1);

        warnLabel = new QLabel(settingsPage);
        warnLabel->setObjectName(QStringLiteral("warnLabel"));
        warnLabel->setStyleSheet(QLatin1String("#warnLabel{   \n"
"color: rgb(255, 0, 0);\n"
"}"));

        gridLayout_2->addWidget(warnLabel, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout_2);

        stackedWidget->addWidget(settingsPage);
        tipPage = new QWidget();
        tipPage->setObjectName(QStringLiteral("tipPage"));
        tipPage->setStyleSheet(QLatin1String("#tipPage{\n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(tipPage);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(110, 50, 110, 60);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(10);
        modifyBtn = new QPushButton(tipPage);
        modifyBtn->setObjectName(QStringLiteral("modifyBtn"));
        modifyBtn->setMinimumSize(QSize(110, 32));
        modifyBtn->setMaximumSize(QSize(110, 32));
        modifyBtn->setStyleSheet(QLatin1String("#modifyBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#modifyBtn:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(modifyBtn, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 2, 1, 1);

        tipLabel = new QLabel(tipPage);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tipLabel->sizePolicy().hasHeightForWidth());
        tipLabel->setSizePolicy(sizePolicy);
        tipLabel->setMinimumSize(QSize(0, 0));
        tipLabel->setMaximumSize(QSize(16777215, 16777215));
        tipLabel->setStyleSheet(QStringLiteral("font-size:14px;"));
        tipLabel->setWordWrap(true);

        gridLayout->addWidget(tipLabel, 0, 1, 1, 3);

        reconnectBtn = new QPushButton(tipPage);
        reconnectBtn->setObjectName(QStringLiteral("reconnectBtn"));
        reconnectBtn->setMinimumSize(QSize(80, 32));
        reconnectBtn->setMaximumSize(QSize(80, 32));
        reconnectBtn->setStyleSheet(QLatin1String("#reconnectBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"}\n"
"#reconnectBtn:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(reconnectBtn, 2, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 3, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        stackedWidget->addWidget(tipPage);
        progressPage = new QWidget();
        progressPage->setObjectName(QStringLiteral("progressPage"));
        progressPage->setStyleSheet(QLatin1String("#progressPage{\n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        gridLayout_3 = new QGridLayout(progressPage);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalSpacer_3 = new QSpacerItem(20, 82, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(146, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        imageLabel = new QLabel(progressPage);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(22, 22));
        imageLabel->setMaximumSize(QSize(22, 22));

        gridLayout_3->addWidget(imageLabel, 1, 1, 1, 1);

        hintLabel = new QLabel(progressPage);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hintLabel->sizePolicy().hasHeightForWidth());
        hintLabel->setSizePolicy(sizePolicy1);
        hintLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(hintLabel, 1, 2, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(146, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 1, 3, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 81, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 2, 2, 1, 1);

        stackedWidget->addWidget(progressPage);

        horizontalLayout_3->addWidget(stackedWidget);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(serverSettingWgt);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(serverSettingWgt);
    } // setupUi

    void retranslateUi(QWidget *serverSettingWgt)
    {
        serverSettingWgt->setWindowTitle(QApplication::translate("serverSettingWgt", "Form", 0));
        cancelBtn->setText(QApplication::translate("serverSettingWgt", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("serverSettingWgt", "\347\241\256\350\256\244", 0));
        label->setText(QApplication::translate("serverSettingWgt", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", 0));
        label_2->setText(QApplication::translate("serverSettingWgt", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\357\274\232", 0));
        warnLabel->setText(QString());
        modifyBtn->setText(QApplication::translate("serverSettingWgt", "\344\277\256\346\224\271\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0));
        tipLabel->setText(QString());
        reconnectBtn->setText(QApplication::translate("serverSettingWgt", "\351\207\215\350\277\236", 0));
        imageLabel->setText(QString());
        hintLabel->setText(QApplication::translate("serverSettingWgt", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250\344\270\255...", 0));
    } // retranslateUi

};

namespace Ui {
    class serverSettingWgt: public Ui_serverSettingWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSETTINGWGT_H
