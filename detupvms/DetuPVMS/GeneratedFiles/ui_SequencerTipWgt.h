/********************************************************************************
** Form generated from reading UI file 'SequencerTipWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCERTIPWGT_H
#define UI_SEQUENCERTIPWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SequencerTipWgt
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *gif_label_;
    QLabel *tip_label_;

    void setupUi(QWidget *SequencerTipWgt)
    {
        if (SequencerTipWgt->objectName().isEmpty())
            SequencerTipWgt->setObjectName(QStringLiteral("SequencerTipWgt"));
        SequencerTipWgt->resize(117, 33);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SequencerTipWgt->sizePolicy().hasHeightForWidth());
        SequencerTipWgt->setSizePolicy(sizePolicy);
        SequencerTipWgt->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(SequencerTipWgt);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(SequencerTipWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"	background:#1E2020;\n"
"	border-radius:5px;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 0, 0, 0);
        gif_label_ = new QLabel(widget);
        gif_label_->setObjectName(QStringLiteral("gif_label_"));
        sizePolicy.setHeightForWidth(gif_label_->sizePolicy().hasHeightForWidth());
        gif_label_->setSizePolicy(sizePolicy);
        gif_label_->setMinimumSize(QSize(29, 29));
        gif_label_->setMaximumSize(QSize(29, 29));

        gridLayout->addWidget(gif_label_, 0, 0, 1, 1);

        tip_label_ = new QLabel(widget);
        tip_label_->setObjectName(QStringLiteral("tip_label_"));
        sizePolicy.setHeightForWidth(tip_label_->sizePolicy().hasHeightForWidth());
        tip_label_->setSizePolicy(sizePolicy);
        tip_label_->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffffff;\n"
"text-align:center;"));

        gridLayout->addWidget(tip_label_, 0, 1, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(SequencerTipWgt);

        QMetaObject::connectSlotsByName(SequencerTipWgt);
    } // setupUi

    void retranslateUi(QWidget *SequencerTipWgt)
    {
        SequencerTipWgt->setWindowTitle(QApplication::translate("SequencerTipWgt", "SequencerTipWgt", 0));
        gif_label_->setText(QString());
        tip_label_->setText(QApplication::translate("SequencerTipWgt", "\346\255\243\345\234\250\345\212\240\350\275\275\344\270\255...", 0));
    } // retranslateUi

};

namespace Ui {
    class SequencerTipWgt: public Ui_SequencerTipWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCERTIPWGT_H
