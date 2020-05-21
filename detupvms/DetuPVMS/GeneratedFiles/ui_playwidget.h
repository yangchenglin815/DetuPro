/********************************************************************************
** Form generated from reading UI file 'playwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYWIDGET_H
#define UI_PLAYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "playmodewgt.h"

QT_BEGIN_NAMESPACE

class Ui_playWidget
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *leftWidget_;
    QVBoxLayout *verticalLayout_2;
    QWidget *devicelistWgt_;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *devicelistlabel_;
    QFrame *line;
    QTreeWidget *treeWidget_;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QWidget *rightWidget_;
    QVBoxLayout *verticalLayout;
    QWidget *gidWidget;
    QGridLayout *gridLayout;
    playModeWgt *playWidget2_;
    playModeWgt *playWidget1_;
    playModeWgt *playWidget3_;
    playModeWgt *playWidget4_;
    QWidget *bottomWidget_;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *originBtn_;
    QPushButton *defaultBtn_;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *singleBtn_;
    QPushButton *fourBtn_;
    QPushButton *fullscreemBtn_;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *playWidget)
    {
        if (playWidget->objectName().isEmpty())
            playWidget->setObjectName(QStringLiteral("playWidget"));
        playWidget->resize(1080, 634);
        gridLayout_2 = new QGridLayout(playWidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(playWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background-color:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        leftWidget_ = new QWidget(widget);
        leftWidget_->setObjectName(QStringLiteral("leftWidget_"));
        leftWidget_->setMinimumSize(QSize(190, 0));
        leftWidget_->setMaximumSize(QSize(190, 16777215));
        leftWidget_->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(leftWidget_);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        devicelistWgt_ = new QWidget(leftWidget_);
        devicelistWgt_->setObjectName(QStringLiteral("devicelistWgt_"));
        devicelistWgt_->setMinimumSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(devicelistWgt_);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 10, -1, 10);
        devicelistlabel_ = new QLabel(devicelistWgt_);
        devicelistlabel_->setObjectName(QStringLiteral("devicelistlabel_"));
        devicelistlabel_->setMinimumSize(QSize(48, 12));
        devicelistlabel_->setMaximumSize(QSize(48, 12));
        devicelistlabel_->setStyleSheet(QString::fromUtf8("\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:left;\n"
""));

        horizontalLayout_4->addWidget(devicelistlabel_);

        line = new QFrame(devicelistWgt_);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(93, 1));
        line->setMaximumSize(QSize(93, 1));
        line->setStyleSheet(QLatin1String("background:#444444;\n"
""));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);


        verticalLayout_3->addLayout(horizontalLayout_4);

        treeWidget_ = new QTreeWidget(devicelistWgt_);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_->setHeaderItem(__qtreewidgetitem);
        treeWidget_->setObjectName(QStringLiteral("treeWidget_"));
        treeWidget_->setStyleSheet(QLatin1String("\n"
"QTreeView {\n"
"        background:#1f2020;\n"
"        border:none;\n"
"      /*  border: 1px solid rgb(50, 50, 50);\n"
"        background-color: rgb(57, 58, 60);*/\n"
"        show-decoration-selected: 1;\n"
"}\n"
"QTreeView::item {\n"
"        height: 30px;\n"
"        color: white;\n"
"        border: none;\n"
"        background-color: transparent;\n"
"}\n"
"QTreeView::item:hover, QTreeView::branch:hover { \n"
"        background-color: rgba(255, 255, 255, 40);\n"
"}\n"
"QTreeView::item:selected, QTreeView::branch:selected { \n"
"        background-color: rgb(50, 50, 50);\n"
"}\n"
"QTreeView::branch {\n"
"      image:none;\n"
"}\n"
"\n"
""));
        treeWidget_->header()->setVisible(false);

        verticalLayout_3->addWidget(treeWidget_);


        verticalLayout_2->addWidget(devicelistWgt_);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(leftWidget_);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(1, 592));
        widget_2->setMaximumSize(QSize(1, 16777215));
        widget_2->setStyleSheet(QLatin1String("transform:rotate(-360deg);\n"
"background:#111111;\n"
""));

        horizontalLayout_2->addWidget(widget_2);

        rightWidget_ = new QWidget(widget);
        rightWidget_->setObjectName(QStringLiteral("rightWidget_"));
        verticalLayout = new QVBoxLayout(rightWidget_);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gidWidget = new QWidget(rightWidget_);
        gidWidget->setObjectName(QStringLiteral("gidWidget"));
        gridLayout = new QGridLayout(gidWidget);
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        playWidget2_ = new playModeWgt(gidWidget);
        playWidget2_->setObjectName(QStringLiteral("playWidget2_"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(playWidget2_->sizePolicy().hasHeightForWidth());
        playWidget2_->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(playWidget2_, 0, 2, 1, 1);

        playWidget1_ = new playModeWgt(gidWidget);
        playWidget1_->setObjectName(QStringLiteral("playWidget1_"));
        sizePolicy1.setHeightForWidth(playWidget1_->sizePolicy().hasHeightForWidth());
        playWidget1_->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(playWidget1_, 0, 0, 1, 1);

        playWidget3_ = new playModeWgt(gidWidget);
        playWidget3_->setObjectName(QStringLiteral("playWidget3_"));
        sizePolicy1.setHeightForWidth(playWidget3_->sizePolicy().hasHeightForWidth());
        playWidget3_->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(playWidget3_, 1, 0, 1, 1);

        playWidget4_ = new playModeWgt(gidWidget);
        playWidget4_->setObjectName(QStringLiteral("playWidget4_"));
        sizePolicy1.setHeightForWidth(playWidget4_->sizePolicy().hasHeightForWidth());
        playWidget4_->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(playWidget4_, 1, 2, 1, 1);


        verticalLayout->addWidget(gidWidget);

        bottomWidget_ = new QWidget(rightWidget_);
        bottomWidget_->setObjectName(QStringLiteral("bottomWidget_"));
        bottomWidget_->setMinimumSize(QSize(0, 62));
        bottomWidget_->setMaximumSize(QSize(16777215, 62));
        bottomWidget_->setStyleSheet(QLatin1String("#bottomWidget_{\n"
"background:rgba(0,0,0,0.70);\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(bottomWidget_);
        horizontalLayout_5->setSpacing(30);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        widget_3 = new QWidget(bottomWidget_);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(15);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        originBtn_ = new QPushButton(widget_3);
        originBtn_->setObjectName(QStringLiteral("originBtn_"));
        originBtn_->setMinimumSize(QSize(34, 34));
        originBtn_->setMaximumSize(QSize(34, 34));
        originBtn_->setStyleSheet(QLatin1String("#originBtn_{\n"
"border-image:url(:/image/image/standardpano.png);\n"
"}\n"
"#originBtn_:hover\n"
"{\n"
"border-image:url(:/image/image/standardpanoc.png);\n"
"}\n"
""));

        horizontalLayout->addWidget(originBtn_);

        defaultBtn_ = new QPushButton(widget_3);
        defaultBtn_->setObjectName(QStringLiteral("defaultBtn_"));
        defaultBtn_->setMinimumSize(QSize(34, 34));
        defaultBtn_->setMaximumSize(QSize(34, 34));
        defaultBtn_->setStyleSheet(QLatin1String("#defaultBtn_{\n"
"border-image:url(:/image/image/360.png);\n"
"}\n"
"#defaultBtn_:hover\n"
"{\n"
"border-image:url(:/image/image/360c.png);\n"
"}\n"
"\n"
""));

        horizontalLayout->addWidget(defaultBtn_);


        horizontalLayout_5->addWidget(widget_3);

        widget_4 = new QWidget(bottomWidget_);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(15);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        singleBtn_ = new QPushButton(widget_4);
        singleBtn_->setObjectName(QStringLiteral("singleBtn_"));
        singleBtn_->setMinimumSize(QSize(34, 34));
        singleBtn_->setMaximumSize(QSize(34, 34));
        singleBtn_->setStyleSheet(QLatin1String("#singleBtn_{\n"
"border-image:url(:/image/image/singlechannel.png);\n"
"}\n"
"#singleBtn_:hover\n"
"{\n"
"border-image:url(:/image/image/singlechannelc.png);\n"
"}"));

        horizontalLayout_3->addWidget(singleBtn_);

        fourBtn_ = new QPushButton(widget_4);
        fourBtn_->setObjectName(QStringLiteral("fourBtn_"));
        fourBtn_->setMinimumSize(QSize(34, 34));
        fourBtn_->setMaximumSize(QSize(34, 34));
        fourBtn_->setStyleSheet(QLatin1String("#fourBtn_{\n"
"border-image:url(:/image/image/4channel.png);\n"
"}\n"
"#fourBtn_:hover\n"
"{\n"
"border-image:url(:/image/image/4channelc.png);\n"
"}\n"
""));

        horizontalLayout_3->addWidget(fourBtn_);


        horizontalLayout_5->addWidget(widget_4);

        fullscreemBtn_ = new QPushButton(bottomWidget_);
        fullscreemBtn_->setObjectName(QStringLiteral("fullscreemBtn_"));
        fullscreemBtn_->setMinimumSize(QSize(34, 34));
        fullscreemBtn_->setMaximumSize(QSize(34, 34));
        fullscreemBtn_->setStyleSheet(QLatin1String("#fullscreemBtn_{\n"
"border-image:url(:/image/image/biger.png);\n"
"}\n"
"#fullscreemBtn_:pressed{\n"
"margin:1px;\n"
"}\n"
"#fullscreemBtn_:hover{\n"
"border-image:url(:/image/image/bigerb.png);\n"
"}\n"
""));

        horizontalLayout_5->addWidget(fullscreemBtn_);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addWidget(bottomWidget_);


        horizontalLayout_2->addWidget(rightWidget_);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(2, 3);

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(playWidget);

        QMetaObject::connectSlotsByName(playWidget);
    } // setupUi

    void retranslateUi(QWidget *playWidget)
    {
        playWidget->setWindowTitle(QApplication::translate("playWidget", "Form", 0));
        devicelistlabel_->setText(QApplication::translate("playWidget", "\350\256\276\345\244\207\345\210\227\350\241\250", 0));
#ifndef QT_NO_TOOLTIP
        originBtn_->setToolTip(QApplication::translate("playWidget", "\345\271\263\351\223\272\350\247\202\347\234\213", 0));
#endif // QT_NO_TOOLTIP
        originBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        defaultBtn_->setToolTip(QApplication::translate("playWidget", "360\302\260\350\247\202\347\234\213", 0));
#endif // QT_NO_TOOLTIP
        defaultBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        singleBtn_->setToolTip(QApplication::translate("playWidget", "\345\215\225\347\252\227\346\240\274", 0));
#endif // QT_NO_TOOLTIP
        singleBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        fourBtn_->setToolTip(QApplication::translate("playWidget", "\345\233\233\347\252\227\346\240\274", 0));
#endif // QT_NO_TOOLTIP
        fourBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        fullscreemBtn_->setToolTip(QApplication::translate("playWidget", "\345\205\250\345\261\217", 0));
#endif // QT_NO_TOOLTIP
        fullscreemBtn_->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class playWidget: public Ui_playWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYWIDGET_H
