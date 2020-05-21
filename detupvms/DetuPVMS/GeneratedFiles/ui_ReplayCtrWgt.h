/********************************************************************************
** Form generated from reading UI file 'ReplayCtrWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLAYCTRWGT_H
#define UI_REPLAYCTRWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "myTimer.h"
#include "setTimeWidget.h"
#include "setdatewidget.h"
#include "speedcontrolwidget.h"

QT_BEGIN_NAMESPACE

class Ui_ReplayCtrWgt
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *rightWidget;
    QGridLayout *gridLayout_2;
    QWidget *widget_;
    QHBoxLayout *horizontalLayout_7;
    setDateWidget *dateWidget_;
    setTimeWidget *timeWidget_;
    speedControlWidget *speedWidget_;
    QPushButton *pauseBtn_;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *fullscreemBtn_;
    myTimer *prograssBarWgt;

    void setupUi(QWidget *ReplayCtrWgt)
    {
        if (ReplayCtrWgt->objectName().isEmpty())
            ReplayCtrWgt->setObjectName(QStringLiteral("ReplayCtrWgt"));
        ReplayCtrWgt->resize(1272, 136);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ReplayCtrWgt->sizePolicy().hasHeightForWidth());
        ReplayCtrWgt->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(ReplayCtrWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(ReplayCtrWgt);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background-color:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        rightWidget = new QWidget(widget);
        rightWidget->setObjectName(QStringLiteral("rightWidget"));
        sizePolicy.setHeightForWidth(rightWidget->sizePolicy().hasHeightForWidth());
        rightWidget->setSizePolicy(sizePolicy);
        rightWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(rightWidget);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_ = new QWidget(rightWidget);
        widget_->setObjectName(QStringLiteral("widget_"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_->sizePolicy().hasHeightForWidth());
        widget_->setSizePolicy(sizePolicy1);
        widget_->setMinimumSize(QSize(0, 62));
        widget_->setMaximumSize(QSize(16777215, 62));
        widget_->setStyleSheet(QLatin1String("#widget_3{\n"
"border-top:1px solid #121212;\n"
"border-bottom:1px solid #121212;\n"
"}"));
        horizontalLayout_7 = new QHBoxLayout(widget_);
        horizontalLayout_7->setSpacing(35);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(15, -1, 20, -1);
        dateWidget_ = new setDateWidget(widget_);
        dateWidget_->setObjectName(QStringLiteral("dateWidget_"));
        dateWidget_->setMinimumSize(QSize(120, 32));
        dateWidget_->setMaximumSize(QSize(16777215, 32));
        dateWidget_->setStyleSheet(QLatin1String("#dateWidget{\n"
"background-color:#1f2020;\n"
"border:none;\n"
"}\n"
""));

        horizontalLayout_7->addWidget(dateWidget_);

        timeWidget_ = new setTimeWidget(widget_);
        timeWidget_->setObjectName(QStringLiteral("timeWidget_"));
        timeWidget_->setMinimumSize(QSize(100, 32));
        timeWidget_->setMaximumSize(QSize(100, 32));

        horizontalLayout_7->addWidget(timeWidget_);

        speedWidget_ = new speedControlWidget(widget_);
        speedWidget_->setObjectName(QStringLiteral("speedWidget_"));
        speedWidget_->setMinimumSize(QSize(118, 32));
        speedWidget_->setMaximumSize(QSize(118, 32));

        horizontalLayout_7->addWidget(speedWidget_);

        pauseBtn_ = new QPushButton(widget_);
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

        horizontalLayout_7->addWidget(pauseBtn_);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);

        fullscreemBtn_ = new QPushButton(widget_);
        fullscreemBtn_->setObjectName(QStringLiteral("fullscreemBtn_"));
        fullscreemBtn_->setMinimumSize(QSize(34, 34));
        fullscreemBtn_->setMaximumSize(QSize(34, 34));
        fullscreemBtn_->setStyleSheet(QLatin1String("#fullscreemBtn{\n"
"border-image:url(:/image/image/biger.png);\n"
"}\n"
"#fullscreemBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#fullscreemBtn:hover{\n"
"border-image:url(:/image/image/bigerb.png);\n"
"}"));

        horizontalLayout_7->addWidget(fullscreemBtn_);


        gridLayout_2->addWidget(widget_, 0, 0, 1, 1);

        prograssBarWgt = new myTimer(rightWidget);
        prograssBarWgt->setObjectName(QStringLiteral("prograssBarWgt"));
        sizePolicy1.setHeightForWidth(prograssBarWgt->sizePolicy().hasHeightForWidth());
        prograssBarWgt->setSizePolicy(sizePolicy1);
        prograssBarWgt->setMinimumSize(QSize(0, 74));
        prograssBarWgt->setMaximumSize(QSize(16777215, 74));
        prograssBarWgt->setStyleSheet(QStringLiteral(""));

        gridLayout_2->addWidget(prograssBarWgt, 1, 0, 1, 1);


        horizontalLayout_2->addWidget(rightWidget);

        horizontalLayout_2->setStretch(0, 3);

        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(ReplayCtrWgt);

        QMetaObject::connectSlotsByName(ReplayCtrWgt);
    } // setupUi

    void retranslateUi(QWidget *ReplayCtrWgt)
    {
        ReplayCtrWgt->setWindowTitle(QApplication::translate("ReplayCtrWgt", "ReplayCtrWgt", 0));
#ifndef QT_NO_TOOLTIP
        speedWidget_->setToolTip(QApplication::translate("ReplayCtrWgt", "\345\277\253\346\224\276/\346\205\242\346\224\276", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pauseBtn_->setToolTip(QApplication::translate("ReplayCtrWgt", "\346\222\255\346\224\276/\346\232\202\345\201\234", 0));
#endif // QT_NO_TOOLTIP
        pauseBtn_->setText(QString());
#ifndef QT_NO_TOOLTIP
        fullscreemBtn_->setToolTip(QApplication::translate("ReplayCtrWgt", "\345\205\250\345\261\217", 0));
#endif // QT_NO_TOOLTIP
        fullscreemBtn_->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ReplayCtrWgt: public Ui_ReplayCtrWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAYCTRWGT_H
