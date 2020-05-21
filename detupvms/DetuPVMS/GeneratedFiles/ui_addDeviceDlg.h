/********************************************************************************
** Form generated from reading UI file 'addDeviceDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDEVICEDLG_H
#define UI_ADDDEVICEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QIPLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_addDeviceDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *addDeviceBtn;
    QPushButton *selectedBtn;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *addDevicePage;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QIPLineEdit *ipLineEdit;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLineEdit *portLineEdit;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *userLineEdit;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QLineEdit *passwdLineEdit;
    QSpacerItem *horizontalSpacer_9;
    QWidget *selectedPage;
    QVBoxLayout *verticalLayout_4;
    QWidget *title;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_5;
    QLabel *label_6;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer;
    QLabel *hintLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *addDeviceDlg)
    {
        if (addDeviceDlg->objectName().isEmpty())
            addDeviceDlg->setObjectName(QStringLiteral("addDeviceDlg"));
        addDeviceDlg->resize(510, 399);
        addDeviceDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#contentWidget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"#addDeviceBtn{\n"
"border:1px solid #cccccc;\n"
"border-top-left-radius:14px;\n"
"border-bottom-left-radius:14px;\n"
"border-right:none;\n"
"color:#888888;\n"
"}\n"
"#addDeviceBtn:checked{\n"
"color:#222222;\n"
"background:#cccccc;\n"
"}\n"
"#selectedBtn{\n"
"border:1px solid #cccccc;\n"
"border-top-right-radius:14px;\n"
"border-bottom-right-radius:14px;\n"
"color:#888888;\n"
"}\n"
"#selectedBtn:checked{\n"
"color:#222222;\n"
"background:#cccccc;\n"
"}\n"
"QLineEdit{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-"
                        "size:12px;\n"
"color:#666666;\n"
"background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"}"));
        verticalLayout = new QVBoxLayout(addDeviceDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(addDeviceDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        contentWidget = new QWidget(addDeviceDlg);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        contentWidget->setStyleSheet(QLatin1String("QLabel{\n"
"color:#666666;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(contentWidget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(105, 20, 85, 40);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        addDeviceBtn = new QPushButton(contentWidget);
        addDeviceBtn->setObjectName(QStringLiteral("addDeviceBtn"));
        addDeviceBtn->setMinimumSize(QSize(80, 28));
        addDeviceBtn->setMaximumSize(QSize(80, 28));
        addDeviceBtn->setCheckable(true);
        addDeviceBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(addDeviceBtn);

        selectedBtn = new QPushButton(contentWidget);
        selectedBtn->setObjectName(QStringLiteral("selectedBtn"));
        selectedBtn->setMinimumSize(QSize(80, 28));
        selectedBtn->setMaximumSize(QSize(80, 28));
        selectedBtn->setCheckable(true);
        selectedBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(selectedBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget = new QStackedWidget(contentWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setMinimumSize(QSize(320, 152));
        stackedWidget->setMaximumSize(QSize(320, 152));
        addDevicePage = new QWidget();
        addDevicePage->setObjectName(QStringLiteral("addDevicePage"));
        verticalLayout_3 = new QVBoxLayout(addDevicePage);
        verticalLayout_3->setSpacing(10);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(addDevicePage);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(36, 0));
        label->setMaximumSize(QSize(36, 16777215));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label, 0, Qt::AlignRight);

        ipLineEdit = new QIPLineEdit(addDevicePage);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(220, 28));
        ipLineEdit->setMaximumSize(QSize(220, 28));

        horizontalLayout_4->addWidget(ipLineEdit);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_2 = new QLabel(addDevicePage);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(36, 0));
        label_2->setMaximumSize(QSize(36, 16777215));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(label_2, 0, Qt::AlignRight);

        portLineEdit = new QLineEdit(addDevicePage);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setMinimumSize(QSize(220, 28));
        portLineEdit->setMaximumSize(QSize(220, 28));

        horizontalLayout_5->addWidget(portLineEdit);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(15);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_3 = new QLabel(addDevicePage);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(36, 0));
        label_3->setMaximumSize(QSize(36, 16777215));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_3, 0, Qt::AlignRight);

        userLineEdit = new QLineEdit(addDevicePage);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));
        userLineEdit->setMinimumSize(QSize(220, 28));
        userLineEdit->setMaximumSize(QSize(220, 28));

        horizontalLayout_6->addWidget(userLineEdit);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_8);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(15);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_4 = new QLabel(addDevicePage);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(36, 0));
        label_4->setMaximumSize(QSize(36, 16777215));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(label_4, 0, Qt::AlignRight);

        passwdLineEdit = new QLineEdit(addDevicePage);
        passwdLineEdit->setObjectName(QStringLiteral("passwdLineEdit"));
        passwdLineEdit->setMinimumSize(QSize(220, 28));
        passwdLineEdit->setMaximumSize(QSize(220, 28));

        horizontalLayout_7->addWidget(passwdLineEdit);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_9);


        verticalLayout_3->addLayout(horizontalLayout_7);

        stackedWidget->addWidget(addDevicePage);
        selectedPage = new QWidget();
        selectedPage->setObjectName(QStringLiteral("selectedPage"));
        verticalLayout_4 = new QVBoxLayout(selectedPage);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        title = new QWidget(selectedPage);
        title->setObjectName(QStringLiteral("title"));
        title->setMinimumSize(QSize(0, 30));
        title->setMaximumSize(QSize(16777215, 30));
        title->setStyleSheet(QLatin1String("#title{\n"
"background:#ffffff;\n"
"border:1px solid #cccccc;\n"
"border-bottom:none;\n"
"}"));
        horizontalLayout_8 = new QHBoxLayout(title);
        horizontalLayout_8->setSpacing(20);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(90, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_5);

        label_5 = new QLabel(title);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_8->addWidget(label_5, 0, Qt::AlignHCenter);

        label_6 = new QLabel(title);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_8->addWidget(label_6, 0, Qt::AlignHCenter);


        verticalLayout_4->addWidget(title);

        listWidget = new QListWidget(selectedPage);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QLatin1String("#listWidget{\n"
"border:1px solid #cccccc;\n"
"}\n"
"QListView:item{\n"
"border-bottom:1px solid #cccccc;\n"
"}\n"
"QListView::item:hover{ \n"
"        background-color: rgba(247, 251, 255);\n"
"}\n"
"QListView::item:selected{ \n"
"        background-color: rgb(206, 227, 253)\n"
"}"));

        verticalLayout_4->addWidget(listWidget);

        stackedWidget->addWidget(selectedPage);

        verticalLayout_2->addWidget(stackedWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        hintLabel = new QLabel(contentWidget);
        hintLabel->setObjectName(QStringLiteral("hintLabel"));
        hintLabel->setStyleSheet(QStringLiteral("color:red;"));

        verticalLayout_2->addWidget(hintLabel, 0, Qt::AlignHCenter);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(12);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        confirmBtn = new QPushButton(contentWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(confirmBtn);

        cancelBtn = new QPushButton(contentWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(contentWidget);


        retranslateUi(addDeviceDlg);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(addDeviceDlg);
    } // setupUi

    void retranslateUi(QDialog *addDeviceDlg)
    {
        addDeviceDlg->setWindowTitle(QApplication::translate("addDeviceDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("addDeviceDlg", "\346\267\273\345\212\240\347\220\203\346\234\272", 0));
        addDeviceBtn->setText(QApplication::translate("addDeviceDlg", "\346\226\260\345\242\236\350\256\276\345\244\207", 0));
        selectedBtn->setText(QApplication::translate("addDeviceDlg", "\345\210\227\350\241\250\351\200\211\346\213\251", 0));
        label->setText(QApplication::translate("addDeviceDlg", "IP\345\234\260\345\235\200", 0));
        label_2->setText(QApplication::translate("addDeviceDlg", "\347\253\257\345\217\243", 0));
        label_3->setText(QApplication::translate("addDeviceDlg", "\347\224\250\346\210\267\345\220\215", 0));
        label_4->setText(QApplication::translate("addDeviceDlg", "\345\257\206\347\240\201", 0));
        label_5->setText(QApplication::translate("addDeviceDlg", "IP", 0));
        label_6->setText(QApplication::translate("addDeviceDlg", "\347\253\257\345\217\243", 0));
        hintLabel->setText(QString());
        confirmBtn->setText(QApplication::translate("addDeviceDlg", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("addDeviceDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class addDeviceDlg: public Ui_addDeviceDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDEVICEDLG_H
