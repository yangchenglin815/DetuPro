/********************************************************************************
** Form generated from reading UI file 'bubbleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUBBLEWIDGET_H
#define UI_BUBBLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "arrowwidget.h"

QT_BEGIN_NAMESPACE

class Ui_bubbleWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    arrowWidget *arrowWgt;
    QWidget *contentWgt;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;

    void setupUi(QWidget *bubbleWidget)
    {
        if (bubbleWidget->objectName().isEmpty())
            bubbleWidget->setObjectName(QStringLiteral("bubbleWidget"));
        bubbleWidget->resize(151, 35);
        bubbleWidget->setMinimumSize(QSize(151, 35));
        bubbleWidget->setMaximumSize(QSize(151, 35));
        horizontalLayout = new QHBoxLayout(bubbleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(bubbleWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        arrowWgt = new arrowWidget(widget);
        arrowWgt->setObjectName(QStringLiteral("arrowWgt"));
        arrowWgt->setMinimumSize(QSize(0, 8));
        arrowWgt->setMaximumSize(QSize(16777215, 8));
        arrowWgt->setStyleSheet(QStringLiteral("color:#323434;"));

        verticalLayout->addWidget(arrowWgt);

        contentWgt = new QWidget(widget);
        contentWgt->setObjectName(QStringLiteral("contentWgt"));
        contentWgt->setStyleSheet(QLatin1String("background:#969696;\n"
"box-shadow:0 2px 6px 0 rgba(0,0,0,0.20);\n"
"border-radius:4px;\n"
""));
        horizontalLayout_2 = new QHBoxLayout(contentWgt);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(contentWgt);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(151, 25));
        label->setMaximumSize(QSize(151, 25));
        label->setStyleSheet(QLatin1String("font-family:PingFangSC-Regular;\n"
"font-size:12px;\n"
"color:#323434;\n"
"\n"
"\n"
""));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        verticalLayout->addWidget(contentWgt);


        horizontalLayout->addWidget(widget);


        retranslateUi(bubbleWidget);

        QMetaObject::connectSlotsByName(bubbleWidget);
    } // setupUi

    void retranslateUi(QWidget *bubbleWidget)
    {
        bubbleWidget->setWindowTitle(QApplication::translate("bubbleWidget", "Form", 0));
        label->setText(QApplication::translate("bubbleWidget", "\350\257\267\350\201\224\347\263\273\346\212\200\346\234\257\346\224\257\346\214\201\350\216\267\345\217\226\345\257\206\347\240\201", 0));
    } // retranslateUi

};

namespace Ui {
    class bubbleWidget: public Ui_bubbleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUBBLEWIDGET_H
