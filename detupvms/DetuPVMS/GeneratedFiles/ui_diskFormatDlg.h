/********************************************************************************
** Form generated from reading UI file 'diskFormatDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISKFORMATDLG_H
#define UI_DISKFORMATDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dlg_titlewgt.h"

QT_BEGIN_NAMESPACE

class Ui_diskFormatDlg
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    dlg_titleWgt *titleWidget;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *diskFormatDlg)
    {
        if (diskFormatDlg->objectName().isEmpty())
            diskFormatDlg->setObjectName(QStringLiteral("diskFormatDlg"));
        diskFormatDlg->resize(412, 257);
        diskFormatDlg->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(diskFormatDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(diskFormatDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"background-color: #eeeeee;\n"
"border-radius:4px;\n"
"}\n"
"QLabel{\n"
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
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 50);
        titleWidget = new dlg_titleWgt(widget);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));

        verticalLayout->addWidget(titleWidget);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

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

        horizontalLayout->addWidget(cancelBtn);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#confirmBtn:hover{\n"
"margin:1px;\n"
"}\n"
""));

        horizontalLayout->addWidget(confirmBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(diskFormatDlg);

        QMetaObject::connectSlotsByName(diskFormatDlg);
    } // setupUi

    void retranslateUi(QDialog *diskFormatDlg)
    {
        diskFormatDlg->setWindowTitle(QApplication::translate("diskFormatDlg", "Dialog", 0));
        label->setText(QApplication::translate("diskFormatDlg", "\346\240\274\345\274\217\345\214\226\345\260\206\345\210\240\351\231\244\347\243\201\347\233\230\345\206\205\346\211\200\346\234\211\346\225\260\346\215\256\344\270\224\344\270\215\345\217\257\346\201\242\345\244\215\357\274\214                                                    \347\241\256\350\256\244\350\246\201\346\240\274\345\274\217\345\214\226\345\220\227\357\274\237", 0));
        cancelBtn->setText(QApplication::translate("diskFormatDlg", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("diskFormatDlg", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class diskFormatDlg: public Ui_diskFormatDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISKFORMATDLG_H
