/********************************************************************************
** Form generated from reading UI file 'setAdminWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETADMINWGT_H
#define UI_SETADMINWGT_H

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
#include <QtWidgets/QWidget>
#include "commonlineedit.h"

QT_BEGIN_NAMESPACE

class Ui_setAdminWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwdLabel;
    QLineEdit *passwdLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *usernameLabel;
    commonLineEdit *usernameLineEdit;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *confirmPasswdLabel;
    QLineEdit *confirmPasswdLineEdit;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *setAdminWgt)
    {
        if (setAdminWgt->objectName().isEmpty())
            setAdminWgt->setObjectName(QStringLiteral("setAdminWgt"));
        setAdminWgt->resize(445, 285);
        horizontalLayout = new QHBoxLayout(setAdminWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(setAdminWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"QPushButton{\n"
" font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}\n"
"QLineEdit{\n"
" background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"}\n"
"QLineEdit:hover{\n"
"border: 1px solid blue;\n"
"}\n"
"QLineEdit:input-placeholder{\n"
"color:#ff0000;\n"
"}\n"
"#widget{\n"
"  \n"
"	background-color: #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(14);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        passwdLabel = new QLabel(widget);
        passwdLabel->setObjectName(QStringLiteral("passwdLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(passwdLabel->sizePolicy().hasHeightForWidth());
        passwdLabel->setSizePolicy(sizePolicy);
        passwdLabel->setMinimumSize(QSize(0, 27));
        passwdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(passwdLabel);

        passwdLineEdit = new QLineEdit(widget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setMinimumSize(QSize(218, 27));
        passwdLineEdit->setStyleSheet(QStringLiteral("padding-left:10px;"));

        horizontalLayout_3->addWidget(passwdLineEdit);


        gridLayout->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        hintLabel = new QLabel(widget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setMinimumSize(QSize(0, 27));
        hintLabel->setStyleSheet(QLatin1String("font-family:PingFangSC-Regular;\n"
"font-size:12px;\n"
"color:#ff0202;\n"
"line-height:12px;\n"
"padding-left:75px;"));
        hintLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(hintLabel);


        gridLayout->addLayout(horizontalLayout_5, 5, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, -1, -1, -1);
        horizontalSpacer_5 = new QSpacerItem(78, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        cancelBtn = new QPushButton(widget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"width:80px;\n"
"height:26px;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_6->addWidget(cancelBtn);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_7);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"width:80px;\n"
"height:26px;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_6->addWidget(confirmBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_6, 6, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(68, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        usernameLabel = new QLabel(widget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        sizePolicy.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy);
        usernameLabel->setMinimumSize(QSize(0, 27));
        usernameLabel->setMaximumSize(QSize(16777215, 16777215));
        usernameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(usernameLabel);

        usernameLineEdit = new commonLineEdit(widget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));
        usernameLineEdit->setMinimumSize(QSize(218, 27));
        usernameLineEdit->setStyleSheet(QLatin1String("\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
""));

        horizontalLayout_2->addWidget(usernameLineEdit);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(67, 26, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(271, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 7, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        confirmPasswdLabel = new QLabel(widget);
        confirmPasswdLabel->setObjectName(QStringLiteral("confirmPasswdLabel"));
        sizePolicy.setHeightForWidth(confirmPasswdLabel->sizePolicy().hasHeightForWidth());
        confirmPasswdLabel->setSizePolicy(sizePolicy);
        confirmPasswdLabel->setMinimumSize(QSize(0, 27));
        confirmPasswdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(confirmPasswdLabel);

        confirmPasswdLineEdit = new QLineEdit(widget);
        confirmPasswdLineEdit->setObjectName(QStringLiteral("confirmPasswdLineEdit"));
        confirmPasswdLineEdit->setMinimumSize(QSize(218, 27));
        confirmPasswdLineEdit->setStyleSheet(QStringLiteral("padding-left:10px;"));

        horizontalLayout_4->addWidget(confirmPasswdLineEdit);


        gridLayout->addLayout(horizontalLayout_4, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(271, 44, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(setAdminWgt);

        QMetaObject::connectSlotsByName(setAdminWgt);
    } // setupUi

    void retranslateUi(QWidget *setAdminWgt)
    {
        setAdminWgt->setWindowTitle(QApplication::translate("setAdminWgt", "Form", 0));
        passwdLabel->setText(QApplication::translate("setAdminWgt", "\345\257\206\347\240\201\357\274\232", 0));
        passwdLineEdit->setPlaceholderText(QString());
        hintLabel->setText(QString());
        cancelBtn->setText(QApplication::translate("setAdminWgt", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("setAdminWgt", "\346\263\250\345\206\214", 0));
        usernameLabel->setText(QApplication::translate("setAdminWgt", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        confirmPasswdLabel->setText(QApplication::translate("setAdminWgt", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", 0));
    } // retranslateUi

};

namespace Ui {
    class setAdminWgt: public Ui_setAdminWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETADMINWGT_H
