/********************************************************************************
** Form generated from reading UI file 'systemSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYSTEMSETTINGDLG_H
#define UI_SYSTEMSETTINGDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qiplineedit.h"

QT_BEGIN_NAMESPACE

class Ui_systemSettingDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *topWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeBtn;
    QHBoxLayout *horizontalLayout_5;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *systemSettingBtn;
    QHBoxLayout *horizontalLayout_19;
    QLabel *systemSettingLbl;
    QWidget *decodeBtn;
    QHBoxLayout *horizontalLayout_18;
    QLabel *decodeLbl;
    QWidget *fileSaveBtn;
    QHBoxLayout *horizontalLayout_23;
    QLabel *fileSaveLbl;
    QPushButton *resetTCSBtn;
    QLabel *AdminLabel;
    QSpacerItem *verticalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_7;
    QLabel *label_8;
    QIPLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_9;
    QLineEdit *portLineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_10;
    QLineEdit *heartLineEdit;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_12;
    QLabel *label_13;
    QRadioButton *hardDecodeBtn;
    QRadioButton *sorfDecodeBtn;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_14;
    QRadioButton *subHardDecodeBtn;
    QRadioButton *subSoftDecodeBtn;
    QSpacerItem *horizontalSpacer_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_27;
    QLabel *label_28;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_16;
    QLineEdit *fileSaveLineEdit;
    QPushButton *scanBtn;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *AdminBtn;
    QWidget *bottomWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *systemSettingDlg)
    {
        if (systemSettingDlg->objectName().isEmpty())
            systemSettingDlg->setObjectName(QStringLiteral("systemSettingDlg"));
        systemSettingDlg->resize(640, 363);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(systemSettingDlg->sizePolicy().hasHeightForWidth());
        systemSettingDlg->setSizePolicy(sizePolicy);
        systemSettingDlg->setMinimumSize(QSize(640, 0));
        systemSettingDlg->setMaximumSize(QSize(640, 16777215));
        systemSettingDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"color:#666666;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#666666;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}\n"
"QRadioButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#666666;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}\n"
"\n"
""));
        horizontalLayout = new QHBoxLayout(systemSettingDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(systemSettingDlg);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"border-radius:4px;\n"
"}"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        topWidget = new QWidget(widget);
        topWidget->setObjectName(QStringLiteral("topWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topWidget->sizePolicy().hasHeightForWidth());
        topWidget->setSizePolicy(sizePolicy1);
        topWidget->setMinimumSize(QSize(0, 32));
        topWidget->setMaximumSize(QSize(16777215, 32));
        topWidget->setStyleSheet(QLatin1String("#topWidget{\n"
"background-color: rgb(255, 255, 255);\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(topWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(230, 11, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(topWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(229, 11, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        closeBtn = new QPushButton(topWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(8, 7));
        closeBtn->setMaximumSize(QSize(8, 7));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
"border-image:url(:/image/image/popupxb);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(closeBtn);


        verticalLayout->addWidget(topWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, 0, -1);
        leftWidget = new QWidget(widget);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        leftWidget->setMinimumSize(QSize(140, 0));
        leftWidget->setMaximumSize(QSize(140, 16777215));
        leftWidget->setStyleSheet(QLatin1String("#leftWidget{\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"QLabel{\n"
"padding-left:35px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        systemSettingBtn = new QWidget(leftWidget);
        systemSettingBtn->setObjectName(QStringLiteral("systemSettingBtn"));
        systemSettingBtn->setMinimumSize(QSize(0, 36));
        systemSettingBtn->setMaximumSize(QSize(16777215, 36));
        horizontalLayout_19 = new QHBoxLayout(systemSettingBtn);
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        horizontalLayout_19->setContentsMargins(0, 0, 0, 0);
        systemSettingLbl = new QLabel(systemSettingBtn);
        systemSettingLbl->setObjectName(QStringLiteral("systemSettingLbl"));
        systemSettingLbl->setMinimumSize(QSize(0, 36));
        systemSettingLbl->setStyleSheet(QLatin1String("systemSettingLbl:hover{\n"
"background-color:#F5F5F5;\n"
"}"));
        systemSettingLbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_19->addWidget(systemSettingLbl);


        verticalLayout_2->addWidget(systemSettingBtn);

        decodeBtn = new QWidget(leftWidget);
        decodeBtn->setObjectName(QStringLiteral("decodeBtn"));
        decodeBtn->setMinimumSize(QSize(0, 36));
        decodeBtn->setMaximumSize(QSize(16777215, 36));
        horizontalLayout_18 = new QHBoxLayout(decodeBtn);
        horizontalLayout_18->setSpacing(0);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        horizontalLayout_18->setContentsMargins(0, 0, 0, 0);
        decodeLbl = new QLabel(decodeBtn);
        decodeLbl->setObjectName(QStringLiteral("decodeLbl"));
        decodeLbl->setMinimumSize(QSize(0, 36));
        decodeLbl->setStyleSheet(QLatin1String("#decodeLbl:hover{\n"
"background-color:#F5F5F5;\n"
"}"));
        decodeLbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(decodeLbl);


        verticalLayout_2->addWidget(decodeBtn);

        fileSaveBtn = new QWidget(leftWidget);
        fileSaveBtn->setObjectName(QStringLiteral("fileSaveBtn"));
        fileSaveBtn->setMinimumSize(QSize(0, 36));
        fileSaveBtn->setMaximumSize(QSize(16777215, 36));
        horizontalLayout_23 = new QHBoxLayout(fileSaveBtn);
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        horizontalLayout_23->setContentsMargins(0, 0, 0, 0);
        fileSaveLbl = new QLabel(fileSaveBtn);
        fileSaveLbl->setObjectName(QStringLiteral("fileSaveLbl"));
        fileSaveLbl->setMinimumSize(QSize(0, 36));
        fileSaveLbl->setStyleSheet(QLatin1String("#fileSaveLbl:hover{\n"
"background-color:#F5F5F5;\n"
"}"));
        fileSaveLbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_23->addWidget(fileSaveLbl);


        verticalLayout_2->addWidget(fileSaveBtn);

        resetTCSBtn = new QPushButton(leftWidget);
        resetTCSBtn->setObjectName(QStringLiteral("resetTCSBtn"));
        resetTCSBtn->setMinimumSize(QSize(0, 36));
        resetTCSBtn->setMaximumSize(QSize(16777215, 36));
        resetTCSBtn->setStyleSheet(QString::fromUtf8("#resetTCSBtn{\n"
"border:none;\n"
"color:#666666;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"line-height:12px;\n"
"}\n"
"#resetTCSBtn:hover{\n"
"background-color:#F5F5F5;\n"
"}\n"
"#resetTCSBtn:checked{\n"
"background-color:#eeeeee;\n"
"}"));
        resetTCSBtn->setCheckable(true);

        verticalLayout_2->addWidget(resetTCSBtn);

        AdminLabel = new QLabel(leftWidget);
        AdminLabel->setObjectName(QStringLiteral("AdminLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(AdminLabel->sizePolicy().hasHeightForWidth());
        AdminLabel->setSizePolicy(sizePolicy2);
        AdminLabel->setMinimumSize(QSize(140, 36));
        AdminLabel->setStyleSheet(QLatin1String("#AdminLabel:hover{\n"
"background-color:#F5F5F5;\n"
"}"));

        verticalLayout_2->addWidget(AdminLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_5->addWidget(leftWidget);

        scrollArea = new QScrollArea(widget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QLatin1String("  QScrollBar:vertical {\n"
"      width:10px;\n"
"      background: #eeeeee;\n"
"      padding-top:6px;\n"
"      padding-bottom:6px;\n"
"padding-right:4px;\n"
"  }\n"
"QScrollBar::handle:vertical{\n"
"    background:rgba(0,0,0,25%);\n"
"    border-radius:2px;\n"
"    min-height:20;\n"
"}\n"
"QScrollBar::handle:vertical:hover\n"
"{\n"
"    background:rgba(0,0,0,50%); \n"
"    border-radius:2px;\n"
"    min-height:20;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"      border: none;\n"
"      background: #eeeeee;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical {\n"
"      border: none;\n"
"      background: #eeeeee;\n"
"}  \n"
"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical  \n"
"{\n"
"    background:#eeeeee;\n"
"    border-radius:4px;\n"
"}\n"
""));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 484, 505));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_8->setSpacing(30);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(30, 25, 55, 30);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(15);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy3);
        label_7->setMinimumSize(QSize(82, 0));
        label_7->setMaximumSize(QSize(82, 16777215));

        horizontalLayout_4->addWidget(label_7);

        label_8 = new QLabel(scrollAreaWidgetContents);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy3.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy3);
        label_8->setMinimumSize(QSize(60, 0));
        label_8->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(label_8);

        ipLineEdit = new QIPLineEdit(scrollAreaWidgetContents);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        sizePolicy2.setHeightForWidth(ipLineEdit->sizePolicy().hasHeightForWidth());
        ipLineEdit->setSizePolicy(sizePolicy2);
        ipLineEdit->setMinimumSize(QSize(220, 28));
        ipLineEdit->setMaximumSize(QSize(220, 28));
        ipLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_4->addWidget(ipLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(15);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));
        sizePolicy3.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy3);
        label_9->setMinimumSize(QSize(157, 0));
        label_9->setMaximumSize(QSize(157, 16777215));
        label_9->setStyleSheet(QStringLiteral("padding-left:94px;"));

        horizontalLayout_6->addWidget(label_9);

        portLineEdit = new QLineEdit(scrollAreaWidgetContents);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        sizePolicy2.setHeightForWidth(portLineEdit->sizePolicy().hasHeightForWidth());
        portLineEdit->setSizePolicy(sizePolicy2);
        portLineEdit->setMinimumSize(QSize(220, 28));
        portLineEdit->setMaximumSize(QSize(220, 28));
        portLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_6->addWidget(portLineEdit);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(15);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));
        sizePolicy3.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy3);
        label_10->setMinimumSize(QSize(158, 0));
        label_10->setMaximumSize(QSize(158, 16777215));
        label_10->setStyleSheet(QStringLiteral("padding-left:94px;"));

        horizontalLayout_7->addWidget(label_10);

        heartLineEdit = new QLineEdit(scrollAreaWidgetContents);
        heartLineEdit->setObjectName(QStringLiteral("heartLineEdit"));
        sizePolicy2.setHeightForWidth(heartLineEdit->sizePolicy().hasHeightForWidth());
        heartLineEdit->setSizePolicy(sizePolicy2);
        heartLineEdit->setMinimumSize(QSize(86, 28));
        heartLineEdit->setMaximumSize(QSize(86, 28));
        heartLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_7->addWidget(heartLineEdit);

        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy3.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy3);
        label_11->setMinimumSize(QSize(119, 0));
        label_11->setMaximumSize(QSize(119, 16777215));

        horizontalLayout_7->addWidget(label_11);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_8->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(15);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(20);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));
        sizePolicy3.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy3);
        label_12->setMinimumSize(QSize(77, 0));
        label_12->setMaximumSize(QSize(77, 16777215));

        horizontalLayout_8->addWidget(label_12);

        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QStringLiteral("label_13"));
        sizePolicy3.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy3);
        label_13->setMinimumSize(QSize(72, 28));
        label_13->setMaximumSize(QSize(72, 16777215));

        horizontalLayout_8->addWidget(label_13);

        hardDecodeBtn = new QRadioButton(scrollAreaWidgetContents);
        hardDecodeBtn->setObjectName(QStringLiteral("hardDecodeBtn"));

        horizontalLayout_8->addWidget(hardDecodeBtn);

        sorfDecodeBtn = new QRadioButton(scrollAreaWidgetContents);
        sorfDecodeBtn->setObjectName(QStringLiteral("sorfDecodeBtn"));

        horizontalLayout_8->addWidget(sorfDecodeBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(20);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_14 = new QLabel(scrollAreaWidgetContents);
        label_14->setObjectName(QStringLiteral("label_14"));
        sizePolicy3.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy3);
        label_14->setMinimumSize(QSize(169, 28));
        label_14->setMaximumSize(QSize(169, 16777215));
        label_14->setStyleSheet(QStringLiteral("padding-left:95px;"));

        horizontalLayout_9->addWidget(label_14);

        subHardDecodeBtn = new QRadioButton(scrollAreaWidgetContents);
        subHardDecodeBtn->setObjectName(QStringLiteral("subHardDecodeBtn"));

        horizontalLayout_9->addWidget(subHardDecodeBtn);

        subSoftDecodeBtn = new QRadioButton(scrollAreaWidgetContents);
        subSoftDecodeBtn->setObjectName(QStringLiteral("subSoftDecodeBtn"));

        horizontalLayout_9->addWidget(subSoftDecodeBtn);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_8);


        verticalLayout_4->addLayout(horizontalLayout_9);


        verticalLayout_8->addLayout(verticalLayout_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(15);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(10);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_27 = new QLabel(scrollAreaWidgetContents);
        label_27->setObjectName(QStringLiteral("label_27"));
        sizePolicy3.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy3);
        label_27->setMaximumSize(QSize(89, 16777215));

        horizontalLayout_16->addWidget(label_27);

        label_28 = new QLabel(scrollAreaWidgetContents);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setMinimumSize(QSize(0, 28));

        horizontalLayout_16->addWidget(label_28);


        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(5);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        horizontalSpacer_16 = new QSpacerItem(95, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_16);

        fileSaveLineEdit = new QLineEdit(scrollAreaWidgetContents);
        fileSaveLineEdit->setObjectName(QStringLiteral("fileSaveLineEdit"));
        sizePolicy2.setHeightForWidth(fileSaveLineEdit->sizePolicy().hasHeightForWidth());
        fileSaveLineEdit->setSizePolicy(sizePolicy2);
        fileSaveLineEdit->setMinimumSize(QSize(240, 28));
        fileSaveLineEdit->setMaximumSize(QSize(240, 28));
        fileSaveLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_17->addWidget(fileSaveLineEdit);

        scanBtn = new QPushButton(scrollAreaWidgetContents);
        scanBtn->setObjectName(QStringLiteral("scanBtn"));
        scanBtn->setMinimumSize(QSize(50, 26));
        scanBtn->setMaximumSize(QSize(50, 26));
        scanBtn->setStyleSheet(QLatin1String("#scanBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"}\n"
"#scanBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_17->addWidget(scanBtn);


        verticalLayout_7->addLayout(horizontalLayout_17);


        verticalLayout_8->addLayout(verticalLayout_7);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(10);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(89, 0));
        label_2->setMaximumSize(QSize(89, 16777215));

        horizontalLayout_10->addWidget(label_2);

        pushButton = new QPushButton(scrollAreaWidgetContents);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 26));
        pushButton->setMaximumSize(QSize(16777215, 26));
        pushButton->setStyleSheet(QLatin1String("#pushButton{\n"
"border:none;\n"
"border-radius:4px;\n"
"background:#ffffff;\n"
"}\n"
"#pushButton:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_10->addWidget(pushButton);


        verticalLayout_8->addLayout(horizontalLayout_10);

        AdminBtn = new QPushButton(scrollAreaWidgetContents);
        AdminBtn->setObjectName(QStringLiteral("AdminBtn"));
        AdminBtn->setMinimumSize(QSize(0, 26));
        AdminBtn->setStyleSheet(QLatin1String("#AdminBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#AdminBtn:pressed{\n"
"margin:1px;\n"
"}"));

        verticalLayout_8->addWidget(AdminBtn);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_5->addWidget(scrollArea);


        verticalLayout->addLayout(horizontalLayout_5);

        bottomWidget = new QWidget(widget);
        bottomWidget->setObjectName(QStringLiteral("bottomWidget"));
        bottomWidget->setMinimumSize(QSize(0, 54));
        bottomWidget->setMaximumSize(QSize(16777215, 54));
        bottomWidget->setStyleSheet(QLatin1String("#bottomWidget{\n"
"border:1px solid #eeeeee;\n"
"border-top-color:#DDDDDD;\n"
"background-color:#EEEEEE;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(bottomWidget);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        saveBtn = new QPushButton(bottomWidget);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));
        saveBtn->setMinimumSize(QSize(80, 30));
        saveBtn->setMaximumSize(QSize(80, 30));
        saveBtn->setStyleSheet(QLatin1String("#saveBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#saveBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(saveBtn);

        cancelBtn = new QPushButton(bottomWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 30));
        cancelBtn->setMaximumSize(QSize(80, 30));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addWidget(bottomWidget);


        horizontalLayout->addWidget(widget);


        retranslateUi(systemSettingDlg);

        QMetaObject::connectSlotsByName(systemSettingDlg);
    } // setupUi

    void retranslateUi(QDialog *systemSettingDlg)
    {
        systemSettingDlg->setWindowTitle(QApplication::translate("systemSettingDlg", "Dialog", 0));
        label->setText(QApplication::translate("systemSettingDlg", "\347\263\273\347\273\237\351\205\215\347\275\256", 0));
        closeBtn->setText(QString());
        systemSettingLbl->setText(QApplication::translate("systemSettingDlg", "  \345\237\272\347\241\200\351\205\215\347\275\256", 0));
        decodeLbl->setText(QApplication::translate("systemSettingDlg", "  \347\274\226\350\247\243\347\240\201\351\205\215\347\275\256", 0));
        fileSaveLbl->setText(QApplication::translate("systemSettingDlg", "  \346\226\207\344\273\266\344\277\235\345\255\230", 0));
        resetTCSBtn->setText(QApplication::translate("systemSettingDlg", "\350\275\254\347\240\201\351\205\215\347\275\256", 0));
        AdminLabel->setText(QApplication::translate("systemSettingDlg", "\347\256\241\347\220\206\345\221\230\350\256\276\347\275\256", 0));
        label_7->setText(QApplication::translate("systemSettingDlg", "\345\237\272\347\241\200\351\205\215\347\275\256\357\274\232", 0));
        label_8->setText(QApplication::translate("systemSettingDlg", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200", 0));
        label_9->setText(QApplication::translate("systemSettingDlg", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243", 0));
        label_10->setText(QApplication::translate("systemSettingDlg", "\350\277\236\346\216\245\345\277\203\350\267\263", 0));
        label_11->setText(QApplication::translate("systemSettingDlg", "\347\247\222\357\274\210\346\224\257\346\214\2013-86400\347\247\222\357\274\211", 0));
        label_12->setText(QApplication::translate("systemSettingDlg", "\347\274\226\350\247\243\347\240\201\351\205\215\347\275\256\357\274\232", 0));
        label_13->setText(QApplication::translate("systemSettingDlg", "\344\270\273\347\240\201\346\265\201\347\274\226\350\247\243\347\240\201", 0));
        hardDecodeBtn->setText(QApplication::translate("systemSettingDlg", "\347\241\254\350\247\243", 0));
        sorfDecodeBtn->setText(QApplication::translate("systemSettingDlg", "\350\275\257\350\247\243", 0));
        label_14->setText(QApplication::translate("systemSettingDlg", "\345\255\220\347\240\201\346\265\201\347\274\226\350\247\243\347\240\201", 0));
        subHardDecodeBtn->setText(QApplication::translate("systemSettingDlg", "\347\241\254\350\247\243", 0));
        subSoftDecodeBtn->setText(QApplication::translate("systemSettingDlg", "\350\275\257\350\247\243", 0));
        label_27->setText(QApplication::translate("systemSettingDlg", "\346\226\207\344\273\266\344\277\235\345\255\230\357\274\232", 0));
        label_28->setText(QApplication::translate("systemSettingDlg", "\346\212\223\345\233\276\346\226\207\344\273\266\345\255\230\345\202\250\350\267\257\345\276\204", 0));
        scanBtn->setText(QApplication::translate("systemSettingDlg", "\346\265\217\350\247\210", 0));
        label_2->setText(QApplication::translate("systemSettingDlg", "\350\275\254\347\240\201\351\205\215\347\275\256\357\274\232", 0));
        pushButton->setText(QApplication::translate("systemSettingDlg", "\351\207\215\347\275\256\350\275\254\347\240\201\351\205\215\347\275\256", 0));
        AdminBtn->setText(QString());
        saveBtn->setText(QApplication::translate("systemSettingDlg", "\344\277\235\345\255\230", 0));
        cancelBtn->setText(QApplication::translate("systemSettingDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class systemSettingDlg: public Ui_systemSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYSTEMSETTINGDLG_H
