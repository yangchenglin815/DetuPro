/********************************************************************************
** Form generated from reading UI file 'detuTittleWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETUTITTLEWGT_H
#define UI_DETUTITTLEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_detuTittleWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_5;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *logo;
    QLabel *logoLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *timeLabel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *unlockBtn;
    QPushButton *settingBtn;
    QPushButton *helpBtn;
    QWidget *sigWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *minimizeBtn;
    QPushButton *maxmizeBtn;
    QPushButton *closeBtn;

    void setupUi(QWidget *detuTittleWgt)
    {
        if (detuTittleWgt->objectName().isEmpty())
            detuTittleWgt->setObjectName(QStringLiteral("detuTittleWgt"));
        detuTittleWgt->resize(1200, 43);
        detuTittleWgt->setMinimumSize(QSize(0, 36));
        detuTittleWgt->setMaximumSize(QSize(16777215, 43));
        detuTittleWgt->setAutoFillBackground(false);
        detuTittleWgt->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(detuTittleWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(detuTittleWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#323232;\n"
"box-shadow:inset 0 1px 0 0 rgba(167,167,170,0.20);\n"
"}\n"
""));
        horizontalLayout_5 = new QHBoxLayout(widget);
        horizontalLayout_5->setSpacing(19);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(15, 0, 18, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setMinimumSize(QSize(0, 18));
        widget_2->setMaximumSize(QSize(16777215, 32));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        logo = new QLabel(widget_2);
        logo->setObjectName(QStringLiteral("logo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logo->sizePolicy().hasHeightForWidth());
        logo->setSizePolicy(sizePolicy1);
        logo->setMinimumSize(QSize(21, 21));
        logo->setMaximumSize(QSize(21, 21));
        logo->setStyleSheet(QLatin1String("#logo{\n"
"border-image:url(:/image/image/monitor.png);\n"
"}"));

        horizontalLayout_3->addWidget(logo);

        logoLabel = new QLabel(widget_2);
        logoLabel->setObjectName(QStringLiteral("logoLabel"));
        sizePolicy1.setHeightForWidth(logoLabel->sizePolicy().hasHeightForWidth());
        logoLabel->setSizePolicy(sizePolicy1);
        logoLabel->setMinimumSize(QSize(80, 0));
        logoLabel->setMaximumSize(QSize(90, 16777215));
        logoLabel->setStyleSheet(QString::fromUtf8("#logoLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#eeeeee;\n"
"line-height:12px;\n"
"text-align:left;\n"
"}"));

        horizontalLayout_3->addWidget(logoLabel);


        horizontalLayout_5->addWidget(widget_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        timeLabel = new QLabel(widget);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));
        timeLabel->setStyleSheet(QString::fromUtf8("#timeLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#eeeeee;\n"
"text-align:left;\n"
"}"));

        horizontalLayout_5->addWidget(timeLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, -1, 5, -1);
        unlockBtn = new QPushButton(widget);
        unlockBtn->setObjectName(QStringLiteral("unlockBtn"));
        unlockBtn->setMinimumSize(QSize(18, 18));
        unlockBtn->setMaximumSize(QSize(18, 18));
        unlockBtn->setStyleSheet(QLatin1String("#unlockBtn{\n"
"border-image: url(:/image/image/unlock.png);\n"
"}\n"
"#unlockBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#unlockBtn:hover{\n"
"border-image:url(:/image/image/unlockb.png);\n"
"}"));
        unlockBtn->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(unlockBtn);

        settingBtn = new QPushButton(widget);
        settingBtn->setObjectName(QStringLiteral("settingBtn"));
        settingBtn->setMinimumSize(QSize(20, 18));
        settingBtn->setMaximumSize(QSize(20, 18));
        settingBtn->setStyleSheet(QLatin1String("#settingBtn{\n"
"border-image: url(:/image/image/setting.png);\n"
"}\n"
"#settingBtn:hover{\n"
"border-image: url(:/image/image/settingb.png);\n"
"}\n"
"#settingBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(settingBtn);

        helpBtn = new QPushButton(widget);
        helpBtn->setObjectName(QStringLiteral("helpBtn"));
        helpBtn->setMinimumSize(QSize(18, 18));
        helpBtn->setMaximumSize(QSize(18, 18));
        helpBtn->setStyleSheet(QLatin1String("#helpBtn{\n"
"border-image: url(:/image/image/help.png);\n"
"}\n"
"#helpBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#helpBtn:hover{\n"
"border-image: url(:/image/image/helpb.png);\n"
"}\n"
""));
        helpBtn->setIconSize(QSize(18, 18));

        horizontalLayout_2->addWidget(helpBtn);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        sigWidget = new QWidget(widget);
        sigWidget->setObjectName(QStringLiteral("sigWidget"));
        sigWidget->setMinimumSize(QSize(1, 20));
        sigWidget->setMaximumSize(QSize(1, 20));
        sigWidget->setStyleSheet(QLatin1String("#sigWidget{\n"
"opacity:0.3;\n"
"background:#000000;\n"
"}"));

        horizontalLayout_5->addWidget(sigWidget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(18);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, -1, 0, -1);
        minimizeBtn = new QPushButton(widget);
        minimizeBtn->setObjectName(QStringLiteral("minimizeBtn"));
        minimizeBtn->setMinimumSize(QSize(10, 10));
        minimizeBtn->setMaximumSize(QSize(10, 10));
        minimizeBtn->setStyleSheet(QLatin1String("#minimizeBtn{\n"
"border-image:url(:/image/image/windowmin.png);\n"
"}\n"
"#minimizeBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#minimizeBtn:hover{\n"
"border-image:url(:/image/image/windowminb.png);\n"
"}"));

        horizontalLayout_4->addWidget(minimizeBtn);

        maxmizeBtn = new QPushButton(widget);
        maxmizeBtn->setObjectName(QStringLiteral("maxmizeBtn"));
        maxmizeBtn->setMinimumSize(QSize(10, 10));
        maxmizeBtn->setMaximumSize(QSize(10, 10));
        maxmizeBtn->setStyleSheet(QLatin1String("#maxmizeBtn{\n"
"border-image:url(:/image/image/windowbiger.png);\n"
"}\n"
"#maxmizeBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#maxmizeBtn:hover{\n"
"border-image:url(:/image/image/windowbigerb.png);\n"
"}"));

        horizontalLayout_4->addWidget(maxmizeBtn);

        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(12, 12));
        closeBtn->setMaximumSize(QSize(12, 12));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
"border-image:url(:/image/image/windowx.png);\n"
"}\n"
"#closeBtn:hover{\n"
"border-image:url(:/image/image/windowxb.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_4->addWidget(closeBtn);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        horizontalLayout->addWidget(widget);


        retranslateUi(detuTittleWgt);

        QMetaObject::connectSlotsByName(detuTittleWgt);
    } // setupUi

    void retranslateUi(QWidget *detuTittleWgt)
    {
        detuTittleWgt->setWindowTitle(QApplication::translate("detuTittleWgt", "Form", 0));
        logo->setText(QString());
        logoLabel->setText(QApplication::translate("detuTittleWgt", "Pano-VMS", 0));
        timeLabel->setText(QApplication::translate("detuTittleWgt", "14:28:30", 0));
#ifndef QT_NO_TOOLTIP
        unlockBtn->setToolTip(QApplication::translate("detuTittleWgt", "\351\224\201\345\256\232", 0));
#endif // QT_NO_TOOLTIP
        unlockBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        settingBtn->setToolTip(QApplication::translate("detuTittleWgt", "\347\263\273\347\273\237\350\256\276\347\275\256", 0));
#endif // QT_NO_TOOLTIP
        settingBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        helpBtn->setToolTip(QApplication::translate("detuTittleWgt", "\345\270\256\345\212\251", 0));
#endif // QT_NO_TOOLTIP
        helpBtn->setText(QString());
        minimizeBtn->setText(QString());
        maxmizeBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class detuTittleWgt: public Ui_detuTittleWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETUTITTLEWGT_H
