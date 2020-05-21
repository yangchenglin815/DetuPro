/********************************************************************************
** Form generated from reading UI file 'MinimapWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MINIMAPWGT_H
#define UI_MINIMAPWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MinimapWgt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *mapWgt_;

    void setupUi(QWidget *MinimapWgt)
    {
        if (MinimapWgt->objectName().isEmpty())
            MinimapWgt->setObjectName(QStringLiteral("MinimapWgt"));
        MinimapWgt->resize(366, 225);
        MinimapWgt->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffffff;\n"
"}\n"
"#titleWidget{\n"
"background:#2A2B2B;\n"
"}\n"
"#closeBtn{\n"
"border-image: url(:/image/image/popupx.png);\n"
"}\n"
"#closeBtn:pressed{\n"
" margin:1px;\n"
"}"));
        verticalLayout = new QVBoxLayout(MinimapWgt);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mapWgt_ = new QWidget(MinimapWgt);
        mapWgt_->setObjectName(QStringLiteral("mapWgt_"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mapWgt_->sizePolicy().hasHeightForWidth());
        mapWgt_->setSizePolicy(sizePolicy);
        mapWgt_->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(mapWgt_);


        retranslateUi(MinimapWgt);

        QMetaObject::connectSlotsByName(MinimapWgt);
    } // setupUi

    void retranslateUi(QWidget *MinimapWgt)
    {
        MinimapWgt->setWindowTitle(QApplication::translate("MinimapWgt", "MinimapWgt", 0));
    } // retranslateUi

};

namespace Ui {
    class MinimapWgt: public Ui_MinimapWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MINIMAPWGT_H
