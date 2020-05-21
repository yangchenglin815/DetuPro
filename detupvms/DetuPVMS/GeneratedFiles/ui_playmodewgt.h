/********************************************************************************
** Form generated from reading UI file 'playmodewgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYMODEWGT_H
#define UI_PLAYMODEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_playModeWgt
{
public:
    QGridLayout *gridLayout_4;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QWidget *topWidget_;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *tipLabel;
    QPushButton *switchStreamBtn_;
    QPushButton *MapBtn_;
    QPushButton *ReplayBtn_;
    QPushButton *hotPointBtn_;
    QPushButton *bandWidthBtn;
    QPushButton *optimize_;
    QPushButton *ballBtn_;
    QPushButton *htcBtn_;
    QPushButton *captureBtn_;
    QPushButton *autoCircleBtn_;
    QScrollArea *scrollArea_;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QWidget *initWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;

    void setupUi(QWidget *playModeWgt)
    {
        if (playModeWgt->objectName().isEmpty())
            playModeWgt->setObjectName(QStringLiteral("playModeWgt"));
        playModeWgt->resize(427, 502);
        gridLayout_4 = new QGridLayout(playModeWgt);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(playModeWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        topWidget_ = new QWidget(widget);
        topWidget_->setObjectName(QStringLiteral("topWidget_"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topWidget_->sizePolicy().hasHeightForWidth());
        topWidget_->setSizePolicy(sizePolicy);
        topWidget_->setMinimumSize(QSize(0, 32));
        topWidget_->setMaximumSize(QSize(16777215, 32));
        topWidget_->setStyleSheet(QLatin1String("#topWidget_{\n"
"background:rgb(0,0,0);\n"
"\n"
"\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(topWidget_);
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label = new QLabel(topWidget_);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(33, 14));
        label->setMaximumSize(QSize(4566456, 14));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffd500;\n"
"text-align:right;\n"
"}"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        tipLabel = new QLabel(topWidget_);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));
        tipLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffffff;\n"
""));

        horizontalLayout_2->addWidget(tipLabel, 0, Qt::AlignHCenter);

        switchStreamBtn_ = new QPushButton(topWidget_);
        switchStreamBtn_->setObjectName(QStringLiteral("switchStreamBtn_"));
        switchStreamBtn_->setMinimumSize(QSize(19, 15));
        switchStreamBtn_->setMaximumSize(QSize(19, 15));
        switchStreamBtn_->setStyleSheet(QLatin1String("#switchStreamBtn_{\n"
"border-image:url(:/image/image/hdclose.png);\n"
"}\n"
"#switchStreamBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#switchStreamBtn_:checked{\n"
"border-image:url(:/image/image/hdopen.png);\n"
"}"));
        switchStreamBtn_->setCheckable(true);

        horizontalLayout_2->addWidget(switchStreamBtn_);

        MapBtn_ = new QPushButton(topWidget_);
        MapBtn_->setObjectName(QStringLiteral("MapBtn_"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(MapBtn_->sizePolicy().hasHeightForWidth());
        MapBtn_->setSizePolicy(sizePolicy2);
        MapBtn_->setMinimumSize(QSize(18, 18));
        MapBtn_->setMaximumSize(QSize(18, 18));
        MapBtn_->setStyleSheet(QLatin1String("#MapBtn_{\n"
"border-image:url(:/image/image/openmap.png);\n"
"}\n"
"#MapBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#MapBtn_:hover{\n"
"border-image:url(:/image/image/openmapb.png);\n"
"}\n"
"#MapBtn_:checked{\n"
"border-image:url(:/image/image/openmapb.png);\n"
"}"));
        MapBtn_->setCheckable(true);

        horizontalLayout_2->addWidget(MapBtn_);

        ReplayBtn_ = new QPushButton(topWidget_);
        ReplayBtn_->setObjectName(QStringLiteral("ReplayBtn_"));
        sizePolicy2.setHeightForWidth(ReplayBtn_->sizePolicy().hasHeightForWidth());
        ReplayBtn_->setSizePolicy(sizePolicy2);
        ReplayBtn_->setMinimumSize(QSize(18, 18));
        ReplayBtn_->setMaximumSize(QSize(18, 18));
        ReplayBtn_->setStyleSheet(QLatin1String("#ReplayBtn_{\n"
"border-image:url(:/image/image/history.png);\n"
"}\n"
"#ReplayBtn_:hover{\n"
"border-image:url(:/image/image/historyb.png);\n"
"}\n"
"#ReplayBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
""));

        horizontalLayout_2->addWidget(ReplayBtn_);

        hotPointBtn_ = new QPushButton(topWidget_);
        hotPointBtn_->setObjectName(QStringLiteral("hotPointBtn_"));
        sizePolicy2.setHeightForWidth(hotPointBtn_->sizePolicy().hasHeightForWidth());
        hotPointBtn_->setSizePolicy(sizePolicy2);
        hotPointBtn_->setMinimumSize(QSize(18, 18));
        hotPointBtn_->setMaximumSize(QSize(18, 18));

        horizontalLayout_2->addWidget(hotPointBtn_);

        bandWidthBtn = new QPushButton(topWidget_);
        bandWidthBtn->setObjectName(QStringLiteral("bandWidthBtn"));
        sizePolicy2.setHeightForWidth(bandWidthBtn->sizePolicy().hasHeightForWidth());
        bandWidthBtn->setSizePolicy(sizePolicy2);
        bandWidthBtn->setMinimumSize(QSize(18, 15));
        bandWidthBtn->setMaximumSize(QSize(18, 15));
        bandWidthBtn->setStyleSheet(QLatin1String("#bandWidthBtn{\n"
"border-image:url(:/image/image/bandWidth.png);\n"
"}\n"
"#bandWidthBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#bandWidthBtn:hover{\n"
"border-image:url(:/image/image/bandWidthb.png);\n"
"}"));

        horizontalLayout_2->addWidget(bandWidthBtn);

        optimize_ = new QPushButton(topWidget_);
        optimize_->setObjectName(QStringLiteral("optimize_"));
        optimize_->setMinimumSize(QSize(18, 18));
        optimize_->setMaximumSize(QSize(18, 18));
        optimize_->setStyleSheet(QLatin1String("#optimize_{\n"
"border-image:url(:/image/image/optimize.png);\n"
"}\n"
"#optimize_:pressed{\n"
"margin:1px;\n"
"}\n"
"#optimize_:hover{\n"
"border-image:url(:/image/image/optimizeb.png);\n"
"}"));

        horizontalLayout_2->addWidget(optimize_);

        ballBtn_ = new QPushButton(topWidget_);
        ballBtn_->setObjectName(QStringLiteral("ballBtn_"));
        ballBtn_->setMinimumSize(QSize(18, 18));
        ballBtn_->setMaximumSize(QSize(18, 18));
        ballBtn_->setStyleSheet(QLatin1String("#ballBtn_{\n"
"border-image:url(:/image/image/ball.png);\n"
"}\n"
"#ballBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#ballBtn_:hover{\n"
"border-image:url(:/image/image/ballb.png);\n"
"}"));

        horizontalLayout_2->addWidget(ballBtn_);

        htcBtn_ = new QPushButton(topWidget_);
        htcBtn_->setObjectName(QStringLiteral("htcBtn_"));
        sizePolicy2.setHeightForWidth(htcBtn_->sizePolicy().hasHeightForWidth());
        htcBtn_->setSizePolicy(sizePolicy2);
        htcBtn_->setMinimumSize(QSize(18, 18));
        htcBtn_->setMaximumSize(QSize(18, 18));
        htcBtn_->setStyleSheet(QLatin1String("#htcBtn_{\n"
"border-image:url(:/image/image/vive.png);\n"
"}\n"
"#htcBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#htcBtn_:hover{\n"
"border-image:url(:/image/image/viveb.png);\n"
"}"));

        horizontalLayout_2->addWidget(htcBtn_);

        captureBtn_ = new QPushButton(topWidget_);
        captureBtn_->setObjectName(QStringLiteral("captureBtn_"));
        captureBtn_->setMinimumSize(QSize(18, 18));
        captureBtn_->setMaximumSize(QSize(18, 18));
        captureBtn_->setStyleSheet(QLatin1String("#captureBtn_{\n"
"border-image:url(:/image/image/capture.png);\n"
"}\n"
"#captureBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#captureBtn_:hover{\n"
"border-image:url(:/image/image/captureb.png);\n"
"}"));

        horizontalLayout_2->addWidget(captureBtn_);

        autoCircleBtn_ = new QPushButton(topWidget_);
        autoCircleBtn_->setObjectName(QStringLiteral("autoCircleBtn_"));
        autoCircleBtn_->setMinimumSize(QSize(18, 18));
        autoCircleBtn_->setMaximumSize(QSize(18, 18));
        autoCircleBtn_->setStyleSheet(QLatin1String("#autoCircleBtn_{\n"
"border-image:url(:/image/image/rotate.png);\n"
"}\n"
"#autoCircleBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#autoCircleBtn_:hover{\n"
"border-image:url(:/image/image/rotateb.png);\n"
"}"));

        horizontalLayout_2->addWidget(autoCircleBtn_);


        gridLayout_3->addWidget(topWidget_, 0, 0, 1, 1);

        scrollArea_ = new QScrollArea(widget);
        scrollArea_->setObjectName(QStringLiteral("scrollArea_"));
        scrollArea_->setMinimumSize(QSize(418, 235));
        scrollArea_->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 425, 233));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        scrollArea_->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea_, 1, 0, 1, 1);

        initWidget = new QWidget(widget);
        initWidget->setObjectName(QStringLiteral("initWidget"));
        sizePolicy.setHeightForWidth(initWidget->sizePolicy().hasHeightForWidth());
        initWidget->setSizePolicy(sizePolicy);
        initWidget->setMinimumSize(QSize(418, 235));
        initWidget->setStyleSheet(QLatin1String("#initWidget{\n"
"background:#323232;\n"
"}"));
        gridLayout = new QGridLayout(initWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(initWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(400, 14));
        label_2->setMaximumSize(QSize(400, 14));
        label_2->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"text-align:center;"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        gridLayout_3->addWidget(initWidget, 2, 0, 1, 1);


        gridLayout_4->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(playModeWgt);

        QMetaObject::connectSlotsByName(playModeWgt);
    } // setupUi

    void retranslateUi(QWidget *playModeWgt)
    {
        playModeWgt->setWindowTitle(QApplication::translate("playModeWgt", "Form", 0));
        label->setText(QString());
        tipLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        switchStreamBtn_->setToolTip(QApplication::translate("playModeWgt", "\345\210\207\346\215\242\347\240\201\346\265\201", 0));
#endif // QT_NO_TOOLTIP
        switchStreamBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        MapBtn_->setToolTip(QApplication::translate("playModeWgt", "<html><head/><body><p>VR\345\234\260\345\233\276</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        MapBtn_->setText(QString());
        ReplayBtn_->setText(QString());
        hotPointBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        bandWidthBtn->setToolTip(QApplication::translate("playModeWgt", "<html><head/><body><p>\345\270\246\345\256\275\347\273\237\350\256\241</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        bandWidthBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        optimize_->setToolTip(QApplication::translate("playModeWgt", "\344\274\230\345\214\226", 0));
#endif // QT_NO_TOOLTIP
        optimize_->setText(QString());
#ifndef QT_NO_TOOLTIP
        ballBtn_->setToolTip(QApplication::translate("playModeWgt", "\347\220\203\346\234\272\350\201\224\345\212\250", 0));
#endif // QT_NO_TOOLTIP
        ballBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        htcBtn_->setToolTip(QApplication::translate("playModeWgt", "Htc\345\244\264\347\233\224", 0));
#endif // QT_NO_TOOLTIP
        htcBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        captureBtn_->setToolTip(QApplication::translate("playModeWgt", "\345\277\253\347\205\247", 0));
#endif // QT_NO_TOOLTIP
        captureBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        autoCircleBtn_->setToolTip(QApplication::translate("playModeWgt", "\350\207\252\345\212\250\346\227\213\350\275\254", 0));
#endif // QT_NO_TOOLTIP
        autoCircleBtn_->setText(QString());
        label_2->setText(QApplication::translate("playModeWgt", "\346\234\252\345\212\240\350\275\275\350\247\206\351\242\221\346\272\220...", 0));
    } // retranslateUi

};

namespace Ui {
    class playModeWgt: public Ui_playModeWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYMODEWGT_H
