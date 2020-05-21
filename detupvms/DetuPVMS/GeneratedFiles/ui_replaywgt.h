/********************************************************************************
** Form generated from reading UI file 'replaywgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLAYWGT_H
#define UI_REPLAYWGT_H

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
#include "myTimer.h"
#include "playmodewgt.h"
#include "setTimeWidget.h"
#include "setdatewidget.h"
#include "speedcontrolwidget.h"

QT_BEGIN_NAMESPACE

class Ui_replayWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout;
    QWidget *playlistWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QFrame *line;
    QTreeWidget *treeWidget_;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QWidget *rightWidget;
    QGridLayout *gridLayout_2;
    QWidget *gidWidget;
    QGridLayout *gridLayout;
    playModeWgt *playWidget1_;
    playModeWgt *playWidget2_;
    playModeWgt *playWidget4_;
    playModeWgt *playWidget3_;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_6;
    setDateWidget *dateWidget;
    setTimeWidget *timeWidget;
    speedControlWidget *speedWidget;
    QPushButton *pauseBtn_;
    QSpacerItem *horizontalSpacer;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *originBtn;
    QPushButton *defaultBtn;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *singleBtn;
    QPushButton *fourBtn;
    QPushButton *fullscreemBtn;
    myTimer *prograssBarWgt;

    void setupUi(QWidget *replayWgt)
    {
        if (replayWgt->objectName().isEmpty())
            replayWgt->setObjectName(QStringLiteral("replayWgt"));
        replayWgt->resize(1231, 365);
        horizontalLayout = new QHBoxLayout(replayWgt);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(replayWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background-color:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        leftWidget = new QWidget(widget);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(25);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftWidget->sizePolicy().hasHeightForWidth());
        leftWidget->setSizePolicy(sizePolicy);
        leftWidget->setMinimumSize(QSize(190, 0));
        leftWidget->setMaximumSize(QSize(190, 16777215));
        leftWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(leftWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        playlistWidget = new QWidget(leftWidget);
        playlistWidget->setObjectName(QStringLiteral("playlistWidget"));
        playlistWidget->setMinimumSize(QSize(0, 0));
        verticalLayout_2 = new QVBoxLayout(playlistWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 10, 0, 10);
        label = new QLabel(playlistWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(48, 12));
        label->setMaximumSize(QSize(48, 12));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:left;\n"
"}"));

        horizontalLayout_3->addWidget(label);

        line = new QFrame(playlistWidget);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(93, 1));
        line->setMaximumSize(QSize(93, 1));
        line->setStyleSheet(QLatin1String("background:#444444;\n"
""));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);


        verticalLayout_2->addLayout(horizontalLayout_3);

        treeWidget_ = new QTreeWidget(playlistWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_->setHeaderItem(__qtreewidgetitem);
        treeWidget_->setObjectName(QStringLiteral("treeWidget_"));
        treeWidget_->setStyleSheet(QLatin1String("QTreeView {\n"
"      background:#1f2020;\n"
"        border:none;\n"
"       /* border: 1px solid rgb(50, 50, 50);\n"
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
""));
        treeWidget_->header()->setVisible(false);

        verticalLayout_2->addWidget(treeWidget_);


        verticalLayout->addWidget(playlistWidget);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(leftWidget);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setMinimumSize(QSize(1, 0));
        line_2->setMaximumSize(QSize(1, 16777215));
        line_2->setStyleSheet(QLatin1String("transform:rotate(-360deg);\n"
"background:#111111;\n"
""));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_2);

        rightWidget = new QWidget(widget);
        rightWidget->setObjectName(QStringLiteral("rightWidget"));
        rightWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(rightWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gidWidget = new QWidget(rightWidget);
        gidWidget->setObjectName(QStringLiteral("gidWidget"));
        gidWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(gidWidget);
        gridLayout->setSpacing(1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(1, 1, 1, 1);
        playWidget1_ = new playModeWgt(gidWidget);
        playWidget1_->setObjectName(QStringLiteral("playWidget1_"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playWidget1_->sizePolicy().hasHeightForWidth());
        playWidget1_->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(playWidget1_, 0, 0, 1, 1);

        playWidget2_ = new playModeWgt(gidWidget);
        playWidget2_->setObjectName(QStringLiteral("playWidget2_"));
        sizePolicy2.setHeightForWidth(playWidget2_->sizePolicy().hasHeightForWidth());
        playWidget2_->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(playWidget2_, 0, 1, 1, 1);

        playWidget4_ = new playModeWgt(gidWidget);
        playWidget4_->setObjectName(QStringLiteral("playWidget4_"));
        sizePolicy2.setHeightForWidth(playWidget4_->sizePolicy().hasHeightForWidth());
        playWidget4_->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(playWidget4_, 1, 1, 1, 1);

        playWidget3_ = new playModeWgt(gidWidget);
        playWidget3_->setObjectName(QStringLiteral("playWidget3_"));
        sizePolicy2.setHeightForWidth(playWidget3_->sizePolicy().hasHeightForWidth());
        playWidget3_->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(playWidget3_, 1, 0, 1, 1);


        gridLayout_2->addWidget(gidWidget, 0, 0, 1, 1);

        widget_3 = new QWidget(rightWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy3);
        widget_3->setMinimumSize(QSize(0, 62));
        widget_3->setMaximumSize(QSize(16777215, 62));
        widget_3->setStyleSheet(QLatin1String("#widget_3{\n"
"border-top:1px solid #121212;\n"
"border-bottom:1px solid #121212;\n"
"}"));
        horizontalLayout_6 = new QHBoxLayout(widget_3);
        horizontalLayout_6->setSpacing(35);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(15, -1, 20, -1);
        dateWidget = new setDateWidget(widget_3);
        dateWidget->setObjectName(QStringLiteral("dateWidget"));
        dateWidget->setMinimumSize(QSize(120, 32));
        dateWidget->setMaximumSize(QSize(16777215, 32));
        dateWidget->setStyleSheet(QLatin1String("#dateWidget{\n"
"background-color:#1f2020;\n"
"border:none;\n"
"}\n"
""));

        horizontalLayout_6->addWidget(dateWidget);

        timeWidget = new setTimeWidget(widget_3);
        timeWidget->setObjectName(QStringLiteral("timeWidget"));
        timeWidget->setMinimumSize(QSize(100, 32));
        timeWidget->setMaximumSize(QSize(100, 32));

        horizontalLayout_6->addWidget(timeWidget);

        speedWidget = new speedControlWidget(widget_3);
        speedWidget->setObjectName(QStringLiteral("speedWidget"));
        speedWidget->setMinimumSize(QSize(118, 32));
        speedWidget->setMaximumSize(QSize(118, 32));

        horizontalLayout_6->addWidget(speedWidget);

        pauseBtn_ = new QPushButton(widget_3);
        pauseBtn_->setObjectName(QStringLiteral("pauseBtn_"));
        pauseBtn_->setMinimumSize(QSize(26, 26));
        pauseBtn_->setMaximumSize(QSize(26, 26));
        pauseBtn_->setStyleSheet(QLatin1String("#pauseBtn_{\n"
"border-image:url(:/image/image/play.png);\n"
"}\n"
"#pauseBtn_:hover{\n"
"border-image:url(:/image/image/playb.png);\n"
"}\n"
"#pauseBtn_:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_6->addWidget(pauseBtn_);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        widget_2 = new QWidget(widget_3);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setSpacing(15);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(15, 0, 15, 0);
        originBtn = new QPushButton(widget_2);
        originBtn->setObjectName(QStringLiteral("originBtn"));
        originBtn->setMinimumSize(QSize(34, 34));
        originBtn->setMaximumSize(QSize(34, 34));

        horizontalLayout_4->addWidget(originBtn);

        defaultBtn = new QPushButton(widget_2);
        defaultBtn->setObjectName(QStringLiteral("defaultBtn"));
        defaultBtn->setMinimumSize(QSize(34, 34));
        defaultBtn->setMaximumSize(QSize(34, 34));

        horizontalLayout_4->addWidget(defaultBtn);


        horizontalLayout_6->addWidget(widget_2);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_5 = new QHBoxLayout(widget_4);
        horizontalLayout_5->setSpacing(15);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(15, 0, 15, 0);
        singleBtn = new QPushButton(widget_4);
        singleBtn->setObjectName(QStringLiteral("singleBtn"));
        singleBtn->setMinimumSize(QSize(34, 34));
        singleBtn->setMaximumSize(QSize(34, 34));

        horizontalLayout_5->addWidget(singleBtn);

        fourBtn = new QPushButton(widget_4);
        fourBtn->setObjectName(QStringLiteral("fourBtn"));
        fourBtn->setMinimumSize(QSize(34, 34));
        fourBtn->setMaximumSize(QSize(34, 34));

        horizontalLayout_5->addWidget(fourBtn);


        horizontalLayout_6->addWidget(widget_4);

        fullscreemBtn = new QPushButton(widget_3);
        fullscreemBtn->setObjectName(QStringLiteral("fullscreemBtn"));
        fullscreemBtn->setMinimumSize(QSize(34, 34));
        fullscreemBtn->setMaximumSize(QSize(34, 34));
        fullscreemBtn->setStyleSheet(QLatin1String("#fullscreemBtn{\n"
"border-image:url(:/image/image/biger.png);\n"
"}\n"
"#fullscreemBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#fullscreemBtn:hover{\n"
"border-image:url(:/image/image/bigerb.png);\n"
"}"));

        horizontalLayout_6->addWidget(fullscreemBtn);


        gridLayout_2->addWidget(widget_3, 1, 0, 1, 1);

        prograssBarWgt = new myTimer(rightWidget);
        prograssBarWgt->setObjectName(QStringLiteral("prograssBarWgt"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(prograssBarWgt->sizePolicy().hasHeightForWidth());
        prograssBarWgt->setSizePolicy(sizePolicy4);
        prograssBarWgt->setMinimumSize(QSize(0, 74));
        prograssBarWgt->setMaximumSize(QSize(16777215, 74));
        prograssBarWgt->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(prograssBarWgt, 2, 0, 1, 1);


        horizontalLayout_2->addWidget(rightWidget);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(2, 3);

        horizontalLayout->addWidget(widget);


        retranslateUi(replayWgt);

        QMetaObject::connectSlotsByName(replayWgt);
    } // setupUi

    void retranslateUi(QWidget *replayWgt)
    {
        replayWgt->setWindowTitle(QApplication::translate("replayWgt", "Form", 0));
        label->setText(QApplication::translate("replayWgt", "\350\256\276\345\244\207\345\210\227\350\241\250", 0));
#ifndef QT_NO_TOOLTIP
        speedWidget->setToolTip(QApplication::translate("replayWgt", "\345\277\253\346\224\276/\346\205\242\346\224\276", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pauseBtn_->setToolTip(QApplication::translate("replayWgt", "\346\222\255\346\224\276/\346\232\202\345\201\234", 0));
#endif // QT_NO_TOOLTIP
        pauseBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        originBtn->setToolTip(QApplication::translate("replayWgt", "\345\271\263\351\223\272\350\247\202\347\234\213", 0));
#endif // QT_NO_TOOLTIP
        originBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        defaultBtn->setToolTip(QApplication::translate("replayWgt", "360\302\260\350\247\202\347\234\213", 0));
#endif // QT_NO_TOOLTIP
        defaultBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        singleBtn->setToolTip(QApplication::translate("replayWgt", "\345\215\225\347\252\227\346\240\274", 0));
#endif // QT_NO_TOOLTIP
        singleBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        fourBtn->setToolTip(QApplication::translate("replayWgt", "\345\233\233\347\252\227\346\240\274", 0));
#endif // QT_NO_TOOLTIP
        fourBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        fullscreemBtn->setToolTip(QApplication::translate("replayWgt", "\345\205\250\345\261\217", 0));
#endif // QT_NO_TOOLTIP
        fullscreemBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class replayWgt: public Ui_replayWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAYWGT_H
