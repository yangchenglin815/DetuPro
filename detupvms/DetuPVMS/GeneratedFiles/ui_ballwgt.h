/********************************************************************************
** Form generated from reading UI file 'ballwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALLWGT_H
#define UI_BALLWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ballWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;

    void setupUi(QWidget *ballWgt)
    {
        if (ballWgt->objectName().isEmpty())
            ballWgt->setObjectName(QStringLiteral("ballWgt"));
        ballWgt->resize(368, 200);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ballWgt->sizePolicy().hasHeightForWidth());
        ballWgt->setSizePolicy(sizePolicy);
        ballWgt->setMinimumSize(QSize(300, 200));
        ballWgt->setMaximumSize(QSize(888888, 888888));
        ballWgt->setAutoFillBackground(false);
        ballWgt->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(ballWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(ballWgt);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(widget);


        retranslateUi(ballWgt);

        QMetaObject::connectSlotsByName(ballWgt);
    } // setupUi

    void retranslateUi(QWidget *ballWgt)
    {
        ballWgt->setWindowTitle(QApplication::translate("ballWgt", "ballWgt", 0));
    } // retranslateUi

};

namespace Ui {
    class ballWgt: public Ui_ballWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALLWGT_H
