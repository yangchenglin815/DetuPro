/********************************************************************************
** Form generated from reading UI file 'progresswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSWIDGET_H
#define UI_PROGRESSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "progresslistview.h"
#include "scalewidget.h"

QT_BEGIN_NAMESPACE

class Ui_progressWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    scaleWidget *widget_3;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    progressListView *listView;

    void setupUi(QWidget *progressWidget)
    {
        if (progressWidget->objectName().isEmpty())
            progressWidget->setObjectName(QStringLiteral("progressWidget"));
        progressWidget->resize(689, 115);
        progressWidget->setStyleSheet(QLatin1String("QWidget#widget{\n"
"/*background:rgba(0,0,0,0.70);*/\n"
"\n"
"}\n"
"#widget_2{\n"
"/*background:rgba(0,0,0,0.70);*/\n"
"}\n"
"QLabel{\n"
"font-family:PingFangSC-Regular;\n"
"font-size:10px;\n"
"color:#a6abab;\n"
"line-height:10px;\n"
"text-align:left;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(progressWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(progressWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(20, 0, 20, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, 0, -1);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(240, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(239, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(16777215, 20));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);

        widget_3 = new scaleWidget(widget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMinimumSize(QSize(0, 20));
        widget_3->setMaximumSize(QSize(16777215, 20));

        verticalLayout->addWidget(widget_3);


        verticalLayout_2->addWidget(widget);

        widget_2 = new QWidget(progressWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QStringLiteral(""));
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(20, 0, 20, 0);
        listView = new progressListView(widget_2);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setStyleSheet(QLatin1String("\n"
"background-color:#1f2020;"));

        horizontalLayout_3->addWidget(listView);


        verticalLayout_2->addWidget(widget_2);


        retranslateUi(progressWidget);

        QMetaObject::connectSlotsByName(progressWidget);
    } // setupUi

    void retranslateUi(QWidget *progressWidget)
    {
        progressWidget->setWindowTitle(QApplication::translate("progressWidget", "Form", 0));
        label->setText(QApplication::translate("progressWidget", "00:00(hr)", 0));
        label_2->setText(QApplication::translate("progressWidget", "12:00", 0));
        label_3->setText(QApplication::translate("progressWidget", "24:00", 0));
    } // retranslateUi

};

namespace Ui {
    class progressWidget: public Ui_progressWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSWIDGET_H
