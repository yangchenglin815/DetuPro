/********************************************************************************
** Form generated from reading UI file 'updateDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPDATEDIALOG_H
#define UI_UPDATEDIALOG_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_updateDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelBtn;
    QPushButton *confirmBtn;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *updateDialog)
    {
        if (updateDialog->objectName().isEmpty())
            updateDialog->setObjectName(QStringLiteral("updateDialog"));
        updateDialog->resize(349, 170);
        horizontalLayout = new QHBoxLayout(updateDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(updateDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"    \n"
"	background-color: #eeeeee;\n"
"border-radius:4px;\n"
"\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"\n"
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
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 0, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(218, 27));
        label->setMaximumSize(QSize(218, 27));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
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

        horizontalLayout_2->addWidget(cancelBtn);

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

        horizontalLayout_2->addWidget(confirmBtn);


        gridLayout->addLayout(horizontalLayout_2, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(updateDialog);

        QMetaObject::connectSlotsByName(updateDialog);
    } // setupUi

    void retranslateUi(QDialog *updateDialog)
    {
        updateDialog->setWindowTitle(QApplication::translate("updateDialog", "Dialog", 0));
        label->setText(QApplication::translate("updateDialog", "\346\243\200\346\265\213\345\210\260\346\234\211\346\226\260\347\211\210\346\234\254\345\217\257\344\273\245\346\233\264\346\226\260\357\274\214\346\230\257\345\220\246\346\233\264\346\226\260\357\274\237", 0));
        cancelBtn->setText(QApplication::translate("updateDialog", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("updateDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class updateDialog: public Ui_updateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPDATEDIALOG_H
