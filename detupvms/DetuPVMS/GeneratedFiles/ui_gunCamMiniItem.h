/********************************************************************************
** Form generated from reading UI file 'gunCamMiniItem.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUNCAMMINIITEM_H
#define UI_GUNCAMMINIITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gunCamMiniItem
{
public:

    void setupUi(QWidget *gunCamMiniItem)
    {
        if (gunCamMiniItem->objectName().isEmpty())
            gunCamMiniItem->setObjectName(QStringLiteral("gunCamMiniItem"));
        gunCamMiniItem->resize(92, 93);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gunCamMiniItem->sizePolicy().hasHeightForWidth());
        gunCamMiniItem->setSizePolicy(sizePolicy);

        retranslateUi(gunCamMiniItem);

        QMetaObject::connectSlotsByName(gunCamMiniItem);
    } // setupUi

    void retranslateUi(QWidget *gunCamMiniItem)
    {
        gunCamMiniItem->setWindowTitle(QApplication::translate("gunCamMiniItem", "gunCamMiniItem", 0));
    } // retranslateUi

};

namespace Ui {
    class gunCamMiniItem: public Ui_gunCamMiniItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUNCAMMINIITEM_H
