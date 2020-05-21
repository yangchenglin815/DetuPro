/********************************************************************************
** Form generated from reading UI file 'showBandWidthDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWBANDWIDTHDLG_H
#define UI_SHOWBANDWIDTHDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_showBandWidthDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *deviceLabel;
    QPushButton *closeBtn;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *bandWidthLabel1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLabel *bandWidthLabel2;
    QSpacerItem *verticalSpacer;
    QPushButton *confirmBtn;

    void setupUi(QDialog *showBandWidthDlg)
    {
        if (showBandWidthDlg->objectName().isEmpty())
            showBandWidthDlg->setObjectName(QStringLiteral("showBandWidthDlg"));
        showBandWidthDlg->resize(381, 237);
        showBandWidthDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"}\n"
"#contentWidget{\n"
"	background-color: #eeeeee;\n"
"    border:1px solid #eeeeee;\n"
"    border-bottom-left-radius:4px;\n"
"    border-bottom-right-radius:4px;\n"
"}\n"
"#titleWidget{\n"
"	background-color: #ffffff;\n"
"    border:1px solid #ffffff;\n"
"    border-top-left-radius:4px;\n"
"    border-top-right-radius:4px;\n"
"}\n"
"#closeBtn{\n"
"border-image:url(:/image/image/popupx.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#closeBtn:hover{\n"
"border-image:url(:/image/image/popupxb.png);\n"
"}\n"
"#confirmBtn{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));
        verticalLayout = new QVBoxLayout(showBandWidthDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(showBandWidthDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(17, 0, -1, 0);
        deviceLabel = new QLabel(titleWidget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));
        deviceLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(deviceLabel);

        closeBtn = new QPushButton(titleWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(8, 8));
        closeBtn->setMaximumSize(QSize(8, 8));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addWidget(titleWidget);

        contentWidget = new QWidget(showBandWidthDlg);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        verticalLayout_3 = new QVBoxLayout(contentWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(50, 50, 50, 30);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(12);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(contentWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label, 0, Qt::AlignRight);

        bandWidthLabel1 = new QLabel(contentWidget);
        bandWidthLabel1->setObjectName(QStringLiteral("bandWidthLabel1"));

        horizontalLayout_2->addWidget(bandWidthLabel1);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(contentWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2, 0, Qt::AlignRight);

        bandWidthLabel2 = new QLabel(contentWidget);
        bandWidthLabel2->setObjectName(QStringLiteral("bandWidthLabel2"));

        horizontalLayout_3->addWidget(bandWidthLabel2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        confirmBtn = new QPushButton(contentWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(confirmBtn, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(contentWidget);


        retranslateUi(showBandWidthDlg);

        QMetaObject::connectSlotsByName(showBandWidthDlg);
    } // setupUi

    void retranslateUi(QDialog *showBandWidthDlg)
    {
        showBandWidthDlg->setWindowTitle(QApplication::translate("showBandWidthDlg", "Dialog", 0));
        deviceLabel->setText(QString());
        closeBtn->setText(QString());
        label->setText(QApplication::translate("showBandWidthDlg", "M1 -> PVS\357\274\232", 0));
        bandWidthLabel1->setText(QApplication::translate("showBandWidthDlg", "0  Byte/s", 0));
        label_2->setText(QApplication::translate("showBandWidthDlg", "PVS -> SRS\357\274\232", 0));
        bandWidthLabel2->setText(QApplication::translate("showBandWidthDlg", "0  Byte/s", 0));
        confirmBtn->setText(QApplication::translate("showBandWidthDlg", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class showBandWidthDlg: public Ui_showBandWidthDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWBANDWIDTHDLG_H
