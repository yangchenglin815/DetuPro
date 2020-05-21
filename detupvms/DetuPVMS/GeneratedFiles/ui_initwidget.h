/********************************************************************************
** Form generated from reading UI file 'initwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITWIDGET_H
#define UI_INITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_initWidget
{
public:
    QGridLayout *gridLayout;
    QLabel *label_;

    void setupUi(QWidget *initWidget)
    {
        if (initWidget->objectName().isEmpty())
            initWidget->setObjectName(QStringLiteral("initWidget"));
        initWidget->resize(400, 18);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(initWidget->sizePolicy().hasHeightForWidth());
        initWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(initWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_ = new QLabel(initWidget);
        label_->setObjectName(QStringLiteral("label_"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_->sizePolicy().hasHeightForWidth());
        label_->setSizePolicy(sizePolicy1);
        label_->setMinimumSize(QSize(400, 14));
        label_->setMaximumSize(QSize(400, 14));
        label_->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"text-align:center;"));
        label_->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_, 0, 0, 1, 1);


        retranslateUi(initWidget);

        QMetaObject::connectSlotsByName(initWidget);
    } // setupUi

    void retranslateUi(QWidget *initWidget)
    {
        initWidget->setWindowTitle(QApplication::translate("initWidget", "initWidget", 0));
        label_->setText(QApplication::translate("initWidget", "\346\234\252\345\212\240\350\275\275\350\247\206\351\242\221\346\272\220...", 0));
    } // retranslateUi

};

namespace Ui {
    class initWidget: public Ui_initWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITWIDGET_H
