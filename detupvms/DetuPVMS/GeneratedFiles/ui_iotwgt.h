/********************************************************************************
** Form generated from reading UI file 'iotwgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOTWGT_H
#define UI_IOTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IOTWgt
{
public:

    void setupUi(QWidget *IOTWgt)
    {
        if (IOTWgt->objectName().isEmpty())
            IOTWgt->setObjectName(QStringLiteral("IOTWgt"));
        IOTWgt->resize(400, 300);

        retranslateUi(IOTWgt);

        QMetaObject::connectSlotsByName(IOTWgt);
    } // setupUi

    void retranslateUi(QWidget *IOTWgt)
    {
        IOTWgt->setWindowTitle(QApplication::translate("IOTWgt", "IOTWgt", 0));
    } // retranslateUi

};

namespace Ui {
    class IOTWgt: public Ui_IOTWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOTWGT_H
