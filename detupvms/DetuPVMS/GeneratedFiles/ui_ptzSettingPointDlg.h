/********************************************************************************
** Form generated from reading UI file 'ptzSettingPointDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTZSETTINGPOINTDLG_H
#define UI_PTZSETTINGPOINTDLG_H

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

class Ui_ptzSettingPointDlg
{
public:
    QGridLayout *gridLayout_2;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *titleLabel;
    QWidget *midWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QWidget *ptzWidget;
    QWidget *bottomWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *ptzSettingPointDlg)
    {
        if (ptzSettingPointDlg->objectName().isEmpty())
            ptzSettingPointDlg->setObjectName(QStringLiteral("ptzSettingPointDlg"));
        ptzSettingPointDlg->resize(1106, 500);
        ptzSettingPointDlg->setStyleSheet(QString::fromUtf8("#ptzSettingPointDlg{\n"
"background:transparent;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#midWidget{\n"
"background:#eeeeee;\n"
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
        gridLayout_2 = new QGridLayout(ptzSettingPointDlg);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(ptzSettingPointDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout_2 = new QHBoxLayout(titleWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout_2->addWidget(titleLabel, 0, Qt::AlignHCenter);


        gridLayout_2->addWidget(titleWidget, 0, 0, 1, 1);

        midWidget = new QWidget(ptzSettingPointDlg);
        midWidget->setObjectName(QStringLiteral("midWidget"));
        horizontalLayout = new QHBoxLayout(midWidget);
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 0, 2, 0);
        widget = new QWidget(midWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(800, 400));
        widget->setMaximumSize(QSize(800, 400));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget);

        ptzWidget = new QWidget(midWidget);
        ptzWidget->setObjectName(QStringLiteral("ptzWidget"));
        sizePolicy.setHeightForWidth(ptzWidget->sizePolicy().hasHeightForWidth());
        ptzWidget->setSizePolicy(sizePolicy);
        ptzWidget->setMinimumSize(QSize(300, 200));
        ptzWidget->setMaximumSize(QSize(300, 200));

        horizontalLayout->addWidget(ptzWidget);


        gridLayout_2->addWidget(midWidget, 1, 0, 1, 1);

        bottomWidget = new QWidget(ptzSettingPointDlg);
        bottomWidget->setObjectName(QStringLiteral("bottomWidget"));
        bottomWidget->setMinimumSize(QSize(0, 68));
        bottomWidget->setMaximumSize(QSize(16777215, 68));
        gridLayout = new QGridLayout(bottomWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(20);
        gridLayout->setVerticalSpacing(0);
        gridLayout->setContentsMargins(-1, 0, -1, 20);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 3, 1, 1);

        confirmBtn = new QPushButton(bottomWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));

        gridLayout->addWidget(confirmBtn, 2, 1, 1, 1);

        cancelBtn = new QPushButton(bottomWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));

        gridLayout->addWidget(cancelBtn, 2, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 1, 1, 1);


        gridLayout_2->addWidget(bottomWidget, 2, 0, 1, 1);


        retranslateUi(ptzSettingPointDlg);

        QMetaObject::connectSlotsByName(ptzSettingPointDlg);
    } // setupUi

    void retranslateUi(QDialog *ptzSettingPointDlg)
    {
        ptzSettingPointDlg->setWindowTitle(QApplication::translate("ptzSettingPointDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("ptzSettingPointDlg", "\347\220\203\346\234\272192.168.2.110", 0));
        label->setText(QString());
        confirmBtn->setText(QApplication::translate("ptzSettingPointDlg", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("ptzSettingPointDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class ptzSettingPointDlg: public Ui_ptzSettingPointDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTZSETTINGPOINTDLG_H
