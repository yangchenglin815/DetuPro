/********************************************************************************
** Form generated from reading UI file 'myTimer.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYTIMER_H
#define UI_MYTIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "timeDurationWidget.h"

QT_BEGIN_NAMESPACE

class Ui_myTimer
{
public:
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    timeDurationWidget *widget;

    void setupUi(QWidget *myTimer)
    {
        if (myTimer->objectName().isEmpty())
            myTimer->setObjectName(QStringLiteral("myTimer"));
        myTimer->resize(1025, 74);
        myTimer->setMinimumSize(QSize(0, 74));
        myTimer->setMaximumSize(QSize(4523545, 74));
        horizontalLayout = new QHBoxLayout(myTimer);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(myTimer);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setStyleSheet(QLatin1String("#scrollArea{\n"
"border:none;\n"
"}\n"
"  QScrollBar:horizontal {\n"
"      height:12px;\n"
"      background: #1f2020;\n"
"      padding-left:14px;\n"
"padding-right: 14px;\n"
"/*padding-bottom:3px;*/\n"
"margin: 0px 165px 0px 0px;\n"
"\n"
"  }\n"
"QScrollBar::handle:horizontal{\n"
"    background:#4e5050;\n"
"    border-radius:4px;\n"
"    min-width:20;\n"
"}\n"
"QScrollBar::handle:horizontal:hover\n"
"{\n"
"    background:#888888; \n"
"    border-radius:4px;\n"
"    min-width:20;\n"
"}\n"
"QScrollBar::add-line:horizontal {\n"
"      /*border: none;\n"
"      background: #1f2020;*/\n"
"border-image:url(:/image/image/right.png);\n"
"}\n"
"QScrollBar::add-line:horizontal:hover {\n"
"border-image:url(:/image/image/rightb.png);\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal:pressed {\n"
"margin:1px;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"     /* border: none;\n"
"      background: #1f2020;*/\n"
"border-image:url(:/image/image/left.png);\n"
"}  \n"
"QScrollBar::sub-line:horizontal:hover {\n"
"border"
                        "-image:url(:/image/image/leftb.png);\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal:pressed {\n"
"margin:1px;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal  \n"
"{\n"
"    background:#1f2020;\n"
"    border-radius:4px;\n"
"}\n"
""));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1025, 62));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents->setStyleSheet(QLatin1String("\n"
"background-color:#1f2020;"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new timeDurationWidget(scrollAreaWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(widget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);


        retranslateUi(myTimer);

        QMetaObject::connectSlotsByName(myTimer);
    } // setupUi

    void retranslateUi(QWidget *myTimer)
    {
        myTimer->setWindowTitle(QApplication::translate("myTimer", "myTimer", 0));
    } // retranslateUi

};

namespace Ui {
    class myTimer: public Ui_myTimer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYTIMER_H
