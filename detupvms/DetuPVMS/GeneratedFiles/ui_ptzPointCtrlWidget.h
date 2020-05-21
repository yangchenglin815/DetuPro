/********************************************************************************
** Form generated from reading UI file 'ptzPointCtrlWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTZPOINTCTRLWIDGET_H
#define UI_PTZPOINTCTRLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ptzPointCtrlWidget
{
public:

    void setupUi(QWidget *ptzPointCtrlWidget)
    {
        if (ptzPointCtrlWidget->objectName().isEmpty())
            ptzPointCtrlWidget->setObjectName(QStringLiteral("ptzPointCtrlWidget"));
        ptzPointCtrlWidget->resize(800, 400);
        ptzPointCtrlWidget->setMinimumSize(QSize(800, 400));
        ptzPointCtrlWidget->setMaximumSize(QSize(800, 400));
        ptzPointCtrlWidget->setStyleSheet(QStringLiteral(""));

        retranslateUi(ptzPointCtrlWidget);

        QMetaObject::connectSlotsByName(ptzPointCtrlWidget);
    } // setupUi

    void retranslateUi(QWidget *ptzPointCtrlWidget)
    {
        ptzPointCtrlWidget->setWindowTitle(QApplication::translate("ptzPointCtrlWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class ptzPointCtrlWidget: public Ui_ptzPointCtrlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTZPOINTCTRLWIDGET_H
