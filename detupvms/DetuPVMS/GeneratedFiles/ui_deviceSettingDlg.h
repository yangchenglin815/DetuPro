/********************************************************************************
** Form generated from reading UI file 'deviceSettingDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICESETTINGDLG_H
#define UI_DEVICESETTINGDLG_H

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
#include "commonComBox.h"

QT_BEGIN_NAMESPACE

class Ui_deviceSettingDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QWidget *topWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *settingsBtn;
    QPushButton *bitSettingsBtn;
    QPushButton *subBitSettingsBtn;
    QSpacerItem *verticalSpacer;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *nameLineEdit;
    QSpacerItem *horizontalSpacer_10;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QRadioButton *upBtn;
    QRadioButton *downBtn;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLabel *label_5;
    commonComBox *resolutionBox;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    commonComBox *framerateBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QLineEdit *bitRateLineEdit;
    QLabel *showLabbel;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_9;
    QRadioButton *vbrBtn;
    QRadioButton *cbrBtn;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_11;
    QLabel *label_10;
    QPushButton *subBitrateBox;
    QSpacerItem *horizontalSpacer_11;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    commonComBox *subResolutionBox;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLabel *subFramerateBox;
    QLabel *label_17;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLineEdit *subBitRateLineEdit;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_16;
    QRadioButton *subVbrBtn;
    QRadioButton *subCbrBtn;
    QSpacerItem *horizontalSpacer_7;
    QWidget *bottomWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *deviceSettingDlg)
    {
        if (deviceSettingDlg->objectName().isEmpty())
            deviceSettingDlg->setObjectName(QStringLiteral("deviceSettingDlg"));
        deviceSettingDlg->resize(640, 390);
        deviceSettingDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#666666;\n"
"}\n"
"QPushButton{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#666666;\n"
"}\n"
"QRadioButton{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#666666;\n"
"}\n"
"QCheckBox{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#666666;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"}\n"
"#topWidget{\n"
"background:#eeeeee;\n"
"}\n"
"#bottomWidget{\n"
"background:#eeeeee;\n"
"}\n"
"#leftWidget{\n"
"background:#ffffff;\n"
"}\n"
"QComboBox{\n"
"border:1px solid #c3caca;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;\n"
"padding-left:10px;\n"
"}\n"
"QComboBox:drop-down{\n"
"subcontrol-origin:padding;\n"
"subcontrol-position:top right;\n"
"width:26px;\n"
"border-left-width: 0px;"
                        "\n"
"border-left-color: gray;\n"
"border-left-style: solid;\n"
"}\n"
"QComboBox:down-arrow{\n"
"image: url(:/image/image/down_arrow.png);\n"
"}\n"
"QComboBox QAbstractItemView{\n"
"background:#f5f5f5;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"selection-background-color:lightgray;\n"
"outline:0px;\n"
"}\n"
"QComboBox QAbstractItemView::item{\n"
"min-height:25px;\n"
"}\n"
"QListView{\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"}\n"
"QListView::item{\n"
"background:#f5f5f5;\n"
"padding-left:8px;\n"
"color:#323434;\n"
"outline:0px;\n"
"}\n"
"QListView::item:hover{\n"
"background: #ffffff;\n"
"color:#323434;\n"
"outline:0px;\n"
"}"));
        verticalLayout = new QVBoxLayout(deviceSettingDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(deviceSettingDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 30));
        titleWidget->setMaximumSize(QSize(16777215, 30));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        topWidget = new QWidget(deviceSettingDlg);
        topWidget->setObjectName(QStringLiteral("topWidget"));
        horizontalLayout_3 = new QHBoxLayout(topWidget);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        leftWidget = new QWidget(topWidget);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        leftWidget->setMinimumSize(QSize(140, 0));
        leftWidget->setMaximumSize(QSize(140, 16777215));
        verticalLayout_2 = new QVBoxLayout(leftWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        settingsBtn = new QPushButton(leftWidget);
        settingsBtn->setObjectName(QStringLiteral("settingsBtn"));
        settingsBtn->setMinimumSize(QSize(0, 36));
        settingsBtn->setMaximumSize(QSize(16777215, 36));
        settingsBtn->setStyleSheet(QLatin1String("#settingsBtn{\n"
"border:none;\n"
"}\n"
"#settingsBtn:hover{\n"
"background:#f5f5f5;\n"
"}\n"
"#settingsBtn:checked{\n"
"background:#eeeeee;\n"
"}"));
        settingsBtn->setCheckable(true);

        verticalLayout_2->addWidget(settingsBtn);

        bitSettingsBtn = new QPushButton(leftWidget);
        bitSettingsBtn->setObjectName(QStringLiteral("bitSettingsBtn"));
        bitSettingsBtn->setMinimumSize(QSize(0, 36));
        bitSettingsBtn->setMaximumSize(QSize(16777215, 36));
        bitSettingsBtn->setStyleSheet(QLatin1String("#bitSettingsBtn{\n"
"border:none;\n"
"}\n"
"#bitSettingsBtn:hover{\n"
"background:#f5f5f5;\n"
"}\n"
"#bitSettingsBtn:checked{\n"
"background:#eeeeee;\n"
"}"));
        bitSettingsBtn->setCheckable(true);

        verticalLayout_2->addWidget(bitSettingsBtn);

        subBitSettingsBtn = new QPushButton(leftWidget);
        subBitSettingsBtn->setObjectName(QStringLiteral("subBitSettingsBtn"));
        subBitSettingsBtn->setMinimumSize(QSize(0, 36));
        subBitSettingsBtn->setMaximumSize(QSize(16777215, 36));
        subBitSettingsBtn->setStyleSheet(QLatin1String("#subBitSettingsBtn{\n"
"border:none;\n"
"}\n"
"#subBitSettingsBtn:hover{\n"
"background:#f5f5f5;\n"
"}\n"
"#subBitSettingsBtn:checked{\n"
"background:#eeeeee;\n"
"}"));
        subBitSettingsBtn->setCheckable(true);

        verticalLayout_2->addWidget(subBitSettingsBtn);

        verticalSpacer = new QSpacerItem(20, 174, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(leftWidget);

        scrollArea = new QScrollArea(topWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QLatin1String("#scrollArea{\n"
"border:none;\n"
"}\n"
"QScrollBar:vertical {\n"
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
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -41, 489, 526));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setSpacing(30);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(30, 12, -1, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(20);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(26);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(48, 0));
        label_2->setMaximumSize(QSize(48, 16777215));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_2);

        nameLineEdit = new QLineEdit(scrollAreaWidgetContents);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setMinimumSize(QSize(200, 28));
        nameLineEdit->setMaximumSize(QSize(300, 28));
        nameLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_4->addWidget(nameLineEdit);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(26);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(90, -1, 90, -1);
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_3);

        upBtn = new QRadioButton(scrollAreaWidgetContents);
        upBtn->setObjectName(QStringLiteral("upBtn"));

        horizontalLayout_6->addWidget(upBtn);

        downBtn = new QRadioButton(scrollAreaWidgetContents);
        downBtn->setObjectName(QStringLiteral("downBtn"));

        horizontalLayout_6->addWidget(downBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_6->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(15);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(16);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(-1, -1, 90, -1);
        label_4 = new QLabel(scrollAreaWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        label_5 = new QLabel(scrollAreaWidgetContents);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(58, 0));
        label_5->setMaximumSize(QSize(48, 16777215));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(label_5);

        resolutionBox = new commonComBox(scrollAreaWidgetContents);
        resolutionBox->setObjectName(QStringLiteral("resolutionBox"));
        resolutionBox->setMinimumSize(QSize(160, 28));
        resolutionBox->setMaximumSize(QSize(160, 28));
        resolutionBox->setEditable(false);
        resolutionBox->setInsertPolicy(QComboBox::InsertAtBottom);
        resolutionBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        resolutionBox->setDuplicatesEnabled(false);
        resolutionBox->setFrame(true);

        horizontalLayout_8->addWidget(resolutionBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(15);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(90, -1, 90, -1);
        label_6 = new QLabel(scrollAreaWidgetContents);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(58, 0));
        label_6->setMaximumSize(QSize(58, 16777215));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_9->addWidget(label_6);

        framerateBox = new commonComBox(scrollAreaWidgetContents);
        framerateBox->setObjectName(QStringLiteral("framerateBox"));
        framerateBox->setMinimumSize(QSize(160, 28));
        framerateBox->setMaximumSize(QSize(160, 28));
        framerateBox->setEditable(false);
        framerateBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        framerateBox->setDuplicatesEnabled(false);
        framerateBox->setFrame(true);

        horizontalLayout_9->addWidget(framerateBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(15);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(90, -1, -1, -1);
        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMinimumSize(QSize(58, 0));
        label_7->setMaximumSize(QSize(58, 16777215));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_10->addWidget(label_7);

        bitRateLineEdit = new QLineEdit(scrollAreaWidgetContents);
        bitRateLineEdit->setObjectName(QStringLiteral("bitRateLineEdit"));
        bitRateLineEdit->setMinimumSize(QSize(120, 28));
        bitRateLineEdit->setMaximumSize(QSize(120, 28));
        bitRateLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_10->addWidget(bitRateLineEdit);

        showLabbel = new QLabel(scrollAreaWidgetContents);
        showLabbel->setObjectName(QStringLiteral("showLabbel"));

        horizontalLayout_10->addWidget(showLabbel);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(26);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(90, -1, 90, -1);
        label_9 = new QLabel(scrollAreaWidgetContents);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(48, 0));
        label_9->setMaximumSize(QSize(48, 16777215));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_9);

        vbrBtn = new QRadioButton(scrollAreaWidgetContents);
        vbrBtn->setObjectName(QStringLiteral("vbrBtn"));

        horizontalLayout_11->addWidget(vbrBtn);

        cbrBtn = new QRadioButton(scrollAreaWidgetContents);
        cbrBtn->setObjectName(QStringLiteral("cbrBtn"));

        horizontalLayout_11->addWidget(cbrBtn);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_11);


        verticalLayout_6->addLayout(verticalLayout_4);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(16);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(0, -1, -1, -1);
        label_11 = new QLabel(scrollAreaWidgetContents);
        label_11->setObjectName(QStringLiteral("label_11"));

        horizontalLayout_17->addWidget(label_11);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));

        horizontalLayout_17->addWidget(label_10);

        subBitrateBox = new QPushButton(scrollAreaWidgetContents);
        subBitrateBox->setObjectName(QStringLiteral("subBitrateBox"));
        subBitrateBox->setMinimumSize(QSize(30, 14));
        subBitrateBox->setMaximumSize(QSize(30, 14));
        subBitrateBox->setStyleSheet(QLatin1String("#subBitrateBox{\n"
"border-image:url(:/image/image/effects.png);\n"
"}\n"
"#subBitrateBox:checked{\n"
"border-image:url(:/image/image/effectsb.png);\n"
"}"));
        subBitrateBox->setCheckable(true);

        horizontalLayout_17->addWidget(subBitrateBox);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_11);


        verticalLayout_6->addLayout(horizontalLayout_17);

        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(15);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(15);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(90, -1, 90, -1);
        label_12 = new QLabel(widget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(58, 0));
        label_12->setMaximumSize(QSize(58, 16777215));
        label_12->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_13->addWidget(label_12);

        subResolutionBox = new commonComBox(widget);
        subResolutionBox->setObjectName(QStringLiteral("subResolutionBox"));
        subResolutionBox->setMinimumSize(QSize(160, 28));
        subResolutionBox->setMaximumSize(QSize(160, 28));
        subResolutionBox->setEditable(false);
        subResolutionBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        subResolutionBox->setDuplicatesEnabled(false);
        subResolutionBox->setFrame(true);

        horizontalLayout_13->addWidget(subResolutionBox);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_8);


        verticalLayout_5->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(15);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(90, -1, 90, -1);
        label_13 = new QLabel(widget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setMinimumSize(QSize(58, 0));
        label_13->setMaximumSize(QSize(58, 16777215));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_14->addWidget(label_13);

        subFramerateBox = new QLabel(widget);
        subFramerateBox->setObjectName(QStringLiteral("subFramerateBox"));
        subFramerateBox->setMinimumSize(QSize(40, 28));
        subFramerateBox->setMaximumSize(QSize(40, 28));
        subFramerateBox->setStyleSheet(QStringLiteral("color:#323434;"));

        horizontalLayout_14->addWidget(subFramerateBox);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setStyleSheet(QStringLiteral("color:#666666;"));

        horizontalLayout_14->addWidget(label_17);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);


        verticalLayout_5->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(15);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(90, -1, -1, -1);
        label_14 = new QLabel(widget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setMinimumSize(QSize(58, 0));
        label_14->setMaximumSize(QSize(58, 16777215));
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_14);

        subBitRateLineEdit = new QLineEdit(widget);
        subBitRateLineEdit->setObjectName(QStringLiteral("subBitRateLineEdit"));
        subBitRateLineEdit->setMinimumSize(QSize(120, 28));
        subBitRateLineEdit->setMaximumSize(QSize(120, 28));
        subBitRateLineEdit->setStyleSheet(QString::fromUtf8("background:#ffffff;\n"
"border:1px solid #c3caca;\n"
"border-radius:2px;\n"
"padding-left:10px;\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#323434;"));

        horizontalLayout_15->addWidget(subBitRateLineEdit);

        label_15 = new QLabel(widget);
        label_15->setObjectName(QStringLiteral("label_15"));

        horizontalLayout_15->addWidget(label_15);


        verticalLayout_5->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(26);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        horizontalLayout_16->setContentsMargins(90, -1, 90, -1);
        label_16 = new QLabel(widget);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMinimumSize(QSize(48, 0));
        label_16->setMaximumSize(QSize(48, 16777215));
        label_16->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_16);

        subVbrBtn = new QRadioButton(widget);
        subVbrBtn->setObjectName(QStringLiteral("subVbrBtn"));

        horizontalLayout_16->addWidget(subVbrBtn);

        subCbrBtn = new QRadioButton(widget);
        subCbrBtn->setObjectName(QStringLiteral("subCbrBtn"));

        horizontalLayout_16->addWidget(subCbrBtn);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_7);


        verticalLayout_5->addLayout(horizontalLayout_16);


        verticalLayout_6->addWidget(widget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_3->addWidget(scrollArea);


        verticalLayout->addWidget(topWidget);

        bottomWidget = new QWidget(deviceSettingDlg);
        bottomWidget->setObjectName(QStringLiteral("bottomWidget"));
        bottomWidget->setMinimumSize(QSize(0, 54));
        bottomWidget->setMaximumSize(QSize(16777215, 54));
        bottomWidget->setStyleSheet(QLatin1String("#bottomWidget{\n"
"border-top:1px solid #dddddd;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(bottomWidget);
        horizontalLayout_2->setSpacing(15);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

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

        horizontalLayout_2->addWidget(saveBtn);

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

        horizontalLayout_2->addWidget(cancelBtn);

        horizontalSpacer_2 = new QSpacerItem(155, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(bottomWidget);


        retranslateUi(deviceSettingDlg);

        QMetaObject::connectSlotsByName(deviceSettingDlg);
    } // setupUi

    void retranslateUi(QDialog *deviceSettingDlg)
    {
        deviceSettingDlg->setWindowTitle(QApplication::translate("deviceSettingDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("deviceSettingDlg", "TextLabel", 0));
        settingsBtn->setText(QApplication::translate("deviceSettingDlg", "\345\237\272\346\234\254\351\205\215\347\275\256", 0));
        bitSettingsBtn->setText(QApplication::translate("deviceSettingDlg", "\344\270\273\347\240\201\346\265\201\351\205\215\347\275\256", 0));
        subBitSettingsBtn->setText(QApplication::translate("deviceSettingDlg", "\345\255\220\347\240\201\346\265\201\351\205\215\347\275\256", 0));
        label->setText(QApplication::translate("deviceSettingDlg", "\345\237\272\346\234\254\351\205\215\347\275\256\357\274\232", 0));
        label_2->setText(QApplication::translate("deviceSettingDlg", " \345\210\253\345\220\215", 0));
        label_3->setText(QApplication::translate("deviceSettingDlg", "\345\256\211\350\243\205\346\226\271\345\274\217", 0));
        upBtn->setText(QApplication::translate("deviceSettingDlg", "\351\225\234\345\244\264\346\234\235\344\270\212", 0));
        downBtn->setText(QApplication::translate("deviceSettingDlg", "\351\225\234\345\244\264\346\234\235\344\270\213", 0));
        label_4->setText(QApplication::translate("deviceSettingDlg", "\344\270\273\347\240\201\346\265\201\351\205\215\347\275\256\357\274\232", 0));
        label_5->setText(QApplication::translate("deviceSettingDlg", "\345\210\206\350\276\250\347\216\207", 0));
        label_6->setText(QApplication::translate("deviceSettingDlg", "\345\270\247\347\216\207", 0));
        label_7->setText(QApplication::translate("deviceSettingDlg", "\347\240\201\347\216\207", 0));
        showLabbel->setText(QApplication::translate("deviceSettingDlg", "kbps  \357\274\2102048~8192\357\274\211", 0));
        label_9->setText(QApplication::translate("deviceSettingDlg", "\347\274\226\347\240\201\346\226\271\345\274\217", 0));
        vbrBtn->setText(QApplication::translate("deviceSettingDlg", "VBR", 0));
        cbrBtn->setText(QApplication::translate("deviceSettingDlg", "CBR", 0));
        label_11->setText(QApplication::translate("deviceSettingDlg", "\345\255\220\347\240\201\346\265\201\351\205\215\347\275\256\357\274\232", 0));
        label_10->setText(QApplication::translate("deviceSettingDlg", "<html><head/><body><p>\345\220\257\347\224\250\345\255\220\347\240\201\346\265\201</p></body></html>", 0));
        subBitrateBox->setText(QString());
        label_12->setText(QApplication::translate("deviceSettingDlg", "\345\210\206\350\276\250\347\216\207", 0));
        label_13->setText(QApplication::translate("deviceSettingDlg", "\345\270\247\347\216\207", 0));
        subFramerateBox->setText(QString());
        label_17->setText(QApplication::translate("deviceSettingDlg", "\357\274\210\344\270\216\344\270\273\347\240\201\346\265\201\345\270\247\347\216\207\344\270\200\350\207\264\357\274\211", 0));
        label_14->setText(QApplication::translate("deviceSettingDlg", "\347\240\201\347\216\207", 0));
        label_15->setText(QApplication::translate("deviceSettingDlg", "kbps  \357\274\210500~3000\357\274\211", 0));
        label_16->setText(QApplication::translate("deviceSettingDlg", "\347\274\226\347\240\201\346\226\271\345\274\217", 0));
        subVbrBtn->setText(QApplication::translate("deviceSettingDlg", "VBR", 0));
        subCbrBtn->setText(QApplication::translate("deviceSettingDlg", "CBR", 0));
        saveBtn->setText(QApplication::translate("deviceSettingDlg", "\344\277\235\345\255\230", 0));
        cancelBtn->setText(QApplication::translate("deviceSettingDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class deviceSettingDlg: public Ui_deviceSettingDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICESETTINGDLG_H
