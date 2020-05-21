/********************************************************************************
** Form generated from reading UI file 'qrCodeDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODEDLG_H
#define UI_QRCODEDLG_H

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
#include "qrCodeGenerateWgt.h"

QT_BEGIN_NAMESPACE

class Ui_qrCodeDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *titleLabel;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeBtn;
    QWidget *qrWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    qrCodeGenerateWgt *qrGenerateWidget;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *qrCodeDlg)
    {
        if (qrCodeDlg->objectName().isEmpty())
            qrCodeDlg->setObjectName(QStringLiteral("qrCodeDlg"));
        qrCodeDlg->resize(440, 320);
        qrCodeDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border:1px solid #ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#qrWidget{\n"
"background:#eeeeee;\n"
"border:1px solid #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"#widget{\n"
"background:#ffffff;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(qrCodeDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(qrCodeDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        closeBtn = new QPushButton(titleWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(10, 10));
        closeBtn->setMaximumSize(QSize(10, 7));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
" border-image:url(:/image/image/popupx2.png);\n"
"}\n"
"#closeBtn:hover{\n"
" border-image:url(:/image/image/popupx2b.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addWidget(titleWidget);

        qrWidget = new QWidget(qrCodeDlg);
        qrWidget->setObjectName(QStringLiteral("qrWidget"));
        gridLayout = new QGridLayout(qrWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(10);
        gridLayout->setContentsMargins(-1, 50, -1, -1);
        label = new QLabel(qrWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        widget = new QWidget(qrWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(160, 160));
        widget->setMaximumSize(QSize(160, 160));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(10, 10, 10, 10);
        qrGenerateWidget = new qrCodeGenerateWgt(widget);
        qrGenerateWidget->setObjectName(QStringLiteral("qrGenerateWidget"));

        gridLayout_2->addWidget(qrGenerateWidget, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 2, 0, 1, 1);


        verticalLayout->addWidget(qrWidget);


        retranslateUi(qrCodeDlg);

        QMetaObject::connectSlotsByName(qrCodeDlg);
    } // setupUi

    void retranslateUi(QDialog *qrCodeDlg)
    {
        qrCodeDlg->setWindowTitle(QApplication::translate("qrCodeDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("qrCodeDlg", "\346\211\253\347\240\201\350\247\202\347\234\213", 0));
        closeBtn->setText(QString());
        label->setText(QApplication::translate("qrCodeDlg", "\350\257\267\347\224\250Pano-VMS APP \346\211\253\347\240\201\350\247\202\347\234\213", 0));
    } // retranslateUi

};

namespace Ui {
    class qrCodeDlg: public Ui_qrCodeDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODEDLG_H
