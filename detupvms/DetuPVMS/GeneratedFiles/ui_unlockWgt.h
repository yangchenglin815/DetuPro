/********************************************************************************
** Form generated from reading UI file 'unlockWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNLOCKWGT_H
#define UI_UNLOCKWGT_H

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

QT_BEGIN_NAMESPACE

class Ui_unlockWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *passwdLabel;
    QLineEdit *passwdLineEdit;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *usernameLabel;
    QLabel *usernameHintLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *hintLabel;

    void setupUi(QWidget *unlockWgt)
    {
        if (unlockWgt->objectName().isEmpty())
            unlockWgt->setObjectName(QStringLiteral("unlockWgt"));
        unlockWgt->resize(400, 300);
        unlockWgt->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font:12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"QPushButton{\n"
"font:12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        horizontalLayout = new QHBoxLayout(unlockWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(unlockWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        passwdLabel = new QLabel(widget);
        passwdLabel->setObjectName(QStringLiteral("passwdLabel"));
        passwdLabel->setMinimumSize(QSize(55, 0));
        passwdLabel->setStyleSheet(QLatin1String("\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;"));
        passwdLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(passwdLabel);

        passwdLineEdit = new QLineEdit(widget);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setMinimumSize(QSize(218, 27));
        passwdLineEdit->setMaximumSize(QSize(218, 27));
        passwdLineEdit->setStyleSheet(QString::fromUtf8("#passwdLineEdit{\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"	padding-left:10px;\n"
"}\n"
"#passwdLineEdit:hover{\n"
"border:1px solid blue;\n"
"}\n"
""));

        horizontalLayout_3->addWidget(passwdLineEdit);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Maximum);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(65, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

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
"}\n"
""));

        horizontalLayout_4->addWidget(confirmBtn);

        horizontalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

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
"}"));

        horizontalLayout_4->addWidget(cancelBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_4, 5, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        usernameLabel = new QLabel(widget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setMinimumSize(QSize(55, 0));
        usernameLabel->setStyleSheet(QLatin1String("\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;"));
        usernameLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(usernameLabel);

        usernameHintLabel = new QLabel(widget);
        usernameHintLabel->setObjectName(QStringLiteral("usernameHintLabel"));
        usernameHintLabel->setMinimumSize(QSize(218, 27));
        usernameHintLabel->setMaximumSize(QSize(218, 27));
        usernameHintLabel->setStyleSheet(QString::fromUtf8("padding-left:10px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;"));

        horizontalLayout_2->addWidget(usernameHintLabel);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 6, 1, 1, 1);

        hintLabel = new QLabel(widget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setStyleSheet(QLatin1String("#hintLabel{\n"
"color: rgb(255, 0, 0);\n"
"padding-left:65px;\n"
"}"));

        gridLayout->addWidget(hintLabel, 3, 1, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(unlockWgt);

        QMetaObject::connectSlotsByName(unlockWgt);
    } // setupUi

    void retranslateUi(QWidget *unlockWgt)
    {
        unlockWgt->setWindowTitle(QApplication::translate("unlockWgt", "Form", 0));
        passwdLabel->setText(QApplication::translate("unlockWgt", "\345\257\206\347\240\201\357\274\232", 0));
        confirmBtn->setText(QApplication::translate("unlockWgt", "\347\241\256\345\256\232", 0));
        cancelBtn->setText(QApplication::translate("unlockWgt", "\345\217\226\346\266\210", 0));
        usernameLabel->setText(QApplication::translate("unlockWgt", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        usernameHintLabel->setText(QString());
        hintLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class unlockWgt: public Ui_unlockWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNLOCKWGT_H
