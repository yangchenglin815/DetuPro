/********************************************************************************
** Form generated from reading UI file 'loginWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "commonlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_loginWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *userLabel;
    commonLineEdit *userLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwdLabel;
    QLineEdit *passwdLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QCheckBox *autoLoginBtn;
    QSpacerItem *horizontalSpacer_3;
    QLabel *forgetBtn;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *loginWidget)
    {
        if (loginWidget->objectName().isEmpty())
            loginWidget->setObjectName(QStringLiteral("loginWidget"));
        loginWidget->resize(424, 277);
        horizontalLayout = new QHBoxLayout(loginWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(loginWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
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
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        userLabel = new QLabel(widget);
        userLabel->setObjectName(QStringLiteral("userLabel"));
        userLabel->setMinimumSize(QSize(50, 0));
        userLabel->setMaximumSize(QSize(50, 16777215));
        userLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(userLabel);

        userLineEdit = new commonLineEdit(widget);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));
        userLineEdit->setMinimumSize(QSize(218, 27));
        userLineEdit->setMaximumSize(QSize(218, 27));
        userLineEdit->setStyleSheet(QLatin1String("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;"));

        horizontalLayout_2->addWidget(userLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        passwdLabel = new QLabel(widget);
        passwdLabel->setObjectName(QStringLiteral("passwdLabel"));
        passwdLabel->setMinimumSize(QSize(50, 0));
        passwdLabel->setMaximumSize(QSize(50, 16777215));
        passwdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(passwdLabel);

        passwdLineEdit = new QLineEdit(widget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setMinimumSize(QSize(218, 27));
        passwdLineEdit->setMaximumSize(QSize(218, 27));
        passwdLineEdit->setAutoFillBackground(false);
        passwdLineEdit->setStyleSheet(QString::fromUtf8("#passwdLineEdit{\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"padding-left:10px;\n"
"}\n"
"#passwdLineEdit:hover{\n"
"border:1px solid blue;\n"
"}\n"
""));

        horizontalLayout_3->addWidget(passwdLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 9, -1);
        horizontalSpacer_5 = new QSpacerItem(55, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        autoLoginBtn = new QCheckBox(widget);
        autoLoginBtn->setObjectName(QStringLiteral("autoLoginBtn"));

        horizontalLayout_4->addWidget(autoLoginBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        forgetBtn = new QLabel(widget);
        forgetBtn->setObjectName(QStringLiteral("forgetBtn"));
        forgetBtn->setStyleSheet(QLatin1String("#forgetBtn{\n"
"   color:#717171;\n"
"}\n"
"#forgetBtn::hover{\n"
"    \n"
"	color: #343434;\n"
"}\n"
""));

        horizontalLayout_4->addWidget(forgetBtn);


        verticalLayout->addLayout(horizontalLayout_4);

        hintLabel = new QLabel(widget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hintLabel->sizePolicy().hasHeightForWidth());
        hintLabel->setSizePolicy(sizePolicy);
        hintLabel->setStyleSheet(QLatin1String("#hintLabel{\n"
"   \n"
"	color: rgb(255, 0, 0);\n"
"}"));
        hintLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(hintLabel);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(55, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        cancelBtn = new QPushButton(widget);
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

        horizontalLayout_5->addWidget(cancelBtn);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_5->addWidget(confirmBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_5);


        gridLayout->addLayout(verticalLayout, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 1, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(loginWidget);

        QMetaObject::connectSlotsByName(loginWidget);
    } // setupUi

    void retranslateUi(QWidget *loginWidget)
    {
        loginWidget->setWindowTitle(QApplication::translate("loginWidget", "Form", 0));
        userLabel->setText(QApplication::translate("loginWidget", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        passwdLabel->setText(QApplication::translate("loginWidget", "\345\257\206\347\240\201\357\274\232", 0));
        autoLoginBtn->setText(QApplication::translate("loginWidget", "\350\207\252\345\212\250\347\231\273\345\275\225", 0));
        forgetBtn->setText(QApplication::translate("loginWidget", "\345\277\230\350\256\260\345\257\206\347\240\201", 0));
        hintLabel->setText(QString());
        cancelBtn->setText(QApplication::translate("loginWidget", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("loginWidget", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class loginWidget: public Ui_loginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
