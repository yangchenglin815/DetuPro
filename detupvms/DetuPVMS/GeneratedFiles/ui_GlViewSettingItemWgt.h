/********************************************************************************
** Form generated from reading UI file 'GlViewSettingItemWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLVIEWSETTINGITEMWGT_H
#define UI_GLVIEWSETTINGITEMWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlViewSettingItemWgt
{
public:

    void setupUi(QWidget *GlViewSettingItemWgt)
    {
        if (GlViewSettingItemWgt->objectName().isEmpty())
            GlViewSettingItemWgt->setObjectName(QStringLiteral("GlViewSettingItemWgt"));
        GlViewSettingItemWgt->resize(92, 100);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GlViewSettingItemWgt->sizePolicy().hasHeightForWidth());
        GlViewSettingItemWgt->setSizePolicy(sizePolicy);
        GlViewSettingItemWgt->setMinimumSize(QSize(35, 100));
        GlViewSettingItemWgt->setMaximumSize(QSize(92, 100));

        retranslateUi(GlViewSettingItemWgt);

        QMetaObject::connectSlotsByName(GlViewSettingItemWgt);
    } // setupUi

    void retranslateUi(QWidget *GlViewSettingItemWgt)
    {
        GlViewSettingItemWgt->setWindowTitle(QApplication::translate("GlViewSettingItemWgt", "GlViewSettingItemWgt", 0));
    } // retranslateUi

};

namespace Ui {
    class GlViewSettingItemWgt: public Ui_GlViewSettingItemWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLVIEWSETTINGITEMWGT_H
