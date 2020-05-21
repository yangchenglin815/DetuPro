/********************************************************************************
** Form generated from reading UI file 'ptzSettingsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTZSETTINGSDLG_H
#define UI_PTZSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qiplineedit.h"

QT_BEGIN_NAMESPACE

class Ui_ptzSettingsDlg
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QWidget *contentWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QIPLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *portLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *userLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *passwdLineEdit;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *cancelBtn;
    QPushButton *confirmBtn;

    void setupUi(QDialog *ptzSettingsDlg)
    {
        if (ptzSettingsDlg->objectName().isEmpty())
            ptzSettingsDlg->setObjectName(QStringLiteral("ptzSettingsDlg"));
        ptzSettingsDlg->resize(520, 374);
        gridLayout = new QGridLayout(ptzSettingsDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ptzSettingsDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
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
"}\n"
"#widget{\n"
"background-color: #eeeeee;\n"
"border-radius:4px;\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(widget);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 33));
        titleWidget->setMaximumSize(QSize(16777215, 33));
        titleWidget->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border:1px solid #ffffff;\n"
"border-radius:4px;"));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_5 = new QLabel(titleWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        contentWidget = new QWidget(widget);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        gridLayout_2 = new QGridLayout(contentWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(6);
        gridLayout_2->setContentsMargins(110, 50, 140, 40);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(15);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(contentWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label);

        ipLineEdit = new QIPLineEdit(contentWidget);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(220, 28));
        ipLineEdit->setMaximumSize(QSize(220, 28));
        ipLineEdit->setStyleSheet(QLatin1String("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;"));

        horizontalLayout_2->addWidget(ipLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(contentWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_2);

        portLineEdit = new QLineEdit(contentWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setMinimumSize(QSize(220, 28));
        portLineEdit->setMaximumSize(QSize(220, 28));
        portLineEdit->setStyleSheet(QLatin1String("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;"));

        horizontalLayout_3->addWidget(portLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(contentWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_3);

        userLineEdit = new QLineEdit(contentWidget);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));
        userLineEdit->setMinimumSize(QSize(220, 28));
        userLineEdit->setMaximumSize(QSize(220, 28));
        userLineEdit->setStyleSheet(QLatin1String("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;"));

        horizontalLayout_4->addWidget(userLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(contentWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_4);

        passwdLineEdit = new QLineEdit(contentWidget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setMinimumSize(QSize(220, 28));
        passwdLineEdit->setMaximumSize(QSize(220, 28));
        passwdLineEdit->setStyleSheet(QLatin1String("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;"));

        horizontalLayout_5->addWidget(passwdLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        hintLabel = new QLabel(contentWidget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(hintLabel->sizePolicy().hasHeightForWidth());
        hintLabel->setSizePolicy(sizePolicy);
        hintLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:red;\n"
"line-height:12px;\n"
"text-align:right;"));
        hintLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(hintLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(20);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(46, -1, 30, -1);
        cancelBtn = new QPushButton(contentWidget);
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

        horizontalLayout_6->addWidget(cancelBtn);

        confirmBtn = new QPushButton(contentWidget);
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

        horizontalLayout_6->addWidget(confirmBtn);


        verticalLayout_2->addLayout(horizontalLayout_6);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(contentWidget);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ptzSettingsDlg);

        QMetaObject::connectSlotsByName(ptzSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *ptzSettingsDlg)
    {
        ptzSettingsDlg->setWindowTitle(QApplication::translate("ptzSettingsDlg", "Dialog", 0));
        label_5->setText(QApplication::translate("ptzSettingsDlg", "\347\273\221\345\256\232\347\220\203\346\234\272", 0));
        label->setText(QApplication::translate("ptzSettingsDlg", "IP\345\234\260\345\235\200", 0));
        label_2->setText(QApplication::translate("ptzSettingsDlg", "\347\253\257\345\217\243", 0));
        label_3->setText(QApplication::translate("ptzSettingsDlg", "\347\224\250\346\210\267\345\220\215", 0));
        label_4->setText(QApplication::translate("ptzSettingsDlg", "\345\257\206\347\240\201", 0));
        hintLabel->setText(QString());
        cancelBtn->setText(QApplication::translate("ptzSettingsDlg", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("ptzSettingsDlg", "\347\273\221\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class ptzSettingsDlg: public Ui_ptzSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTZSETTINGSDLG_H
