/********************************************************************************
** Form generated from reading UI file 'spySettingPointDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPYSETTINGPOINTDLG_H
#define UI_SPYSETTINGPOINTDLG_H

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

QT_BEGIN_NAMESPACE

class Ui_spySettingPointDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QWidget *midWidget;
    QWidget *bottomWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;

    void setupUi(QDialog *spySettingPointDlg)
    {
        if (spySettingPointDlg->objectName().isEmpty())
            spySettingPointDlg->setObjectName(QStringLiteral("spySettingPointDlg"));
        spySettingPointDlg->resize(720, 460);
        spySettingPointDlg->setStyleSheet(QString::fromUtf8("#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#bottomWidget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));
        verticalLayout = new QVBoxLayout(spySettingPointDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(spySettingPointDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(titleWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        midWidget = new QWidget(spySettingPointDlg);
        midWidget->setObjectName(QStringLiteral("midWidget"));
        midWidget->setMinimumSize(QSize(0, 360));
        midWidget->setMaximumSize(QSize(16777215, 360));

        verticalLayout->addWidget(midWidget);

        bottomWidget = new QWidget(spySettingPointDlg);
        bottomWidget->setObjectName(QStringLiteral("bottomWidget"));
        gridLayout = new QGridLayout(bottomWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(12);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 20);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 3, 1, 1);

        confirmBtn = new QPushButton(bottomWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(confirmBtn, 1, 1, 1, 1);

        cancelBtn = new QPushButton(bottomWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(cancelBtn, 1, 2, 1, 1);


        verticalLayout->addWidget(bottomWidget);


        retranslateUi(spySettingPointDlg);

        QMetaObject::connectSlotsByName(spySettingPointDlg);
    } // setupUi

    void retranslateUi(QDialog *spySettingPointDlg)
    {
        spySettingPointDlg->setWindowTitle(QApplication::translate("spySettingPointDlg", "Dialog", 0));
        label->setText(QApplication::translate("spySettingPointDlg", "\346\236\252\346\234\272192.168.2.118", 0));
        confirmBtn->setText(QApplication::translate("spySettingPointDlg", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("spySettingPointDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class spySettingPointDlg: public Ui_spySettingPointDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPYSETTINGPOINTDLG_H
