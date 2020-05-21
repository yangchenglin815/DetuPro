/********************************************************************************
** Form generated from reading UI file 'GlViewSetingWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLVIEWSETINGWGT_H
#define UI_GLVIEWSETINGWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlViewSetingWgt
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *text_label_;
    QLabel *img_label_;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *GlViewSetingWgt)
    {
        if (GlViewSetingWgt->objectName().isEmpty())
            GlViewSetingWgt->setObjectName(QStringLiteral("GlViewSetingWgt"));
        GlViewSetingWgt->resize(176, 144);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(GlViewSetingWgt->sizePolicy().hasHeightForWidth());
        GlViewSetingWgt->setSizePolicy(sizePolicy);
        GlViewSetingWgt->setMinimumSize(QSize(176, 144));
        GlViewSetingWgt->setMaximumSize(QSize(176, 144));
        GlViewSetingWgt->setSizeIncrement(QSize(200, 200));
        GlViewSetingWgt->setStyleSheet(QLatin1String("#widget{\n"
"background:rgba(0,0,0,0.7);\n"
"border-radius:4px;\n"
"}"));
        gridLayout_2 = new QGridLayout(GlViewSetingWgt);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(GlViewSetingWgt);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(9);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(8, 5, 8, 5);
        text_label_ = new QLabel(widget);
        text_label_->setObjectName(QStringLiteral("text_label_"));
        text_label_->setStyleSheet(QString::fromUtf8("#text_label_{\n"
"/*background-color:rgba(0,0,0,0.7);*/\n"
"border-radius:15px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgba(255,255,255,1);\n"
"}"));
        text_label_->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(text_label_);

        img_label_ = new QLabel(widget);
        img_label_->setObjectName(QStringLiteral("img_label_"));
        sizePolicy.setHeightForWidth(img_label_->sizePolicy().hasHeightForWidth());
        img_label_->setSizePolicy(sizePolicy);
        img_label_->setMinimumSize(QSize(160, 80));
        img_label_->setMaximumSize(QSize(160, 80));

        verticalLayout->addWidget(img_label_);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(50, 20));
        confirmBtn->setMaximumSize(QSize(50, 20));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:10px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout->addWidget(confirmBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(GlViewSetingWgt);

        QMetaObject::connectSlotsByName(GlViewSetingWgt);
    } // setupUi

    void retranslateUi(QWidget *GlViewSetingWgt)
    {
        GlViewSetingWgt->setWindowTitle(QApplication::translate("GlViewSetingWgt", "GviewSetingWgt", 0));
        text_label_->setText(QApplication::translate("GlViewSetingWgt", "\347\247\273\345\212\250\350\207\263\345\234\260\345\233\276\346\255\243\344\270\212\346\226\271\345\234\272\346\231\257", 0));
        img_label_->setText(QString());
        confirmBtn->setText(QApplication::translate("GlViewSetingWgt", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class GlViewSetingWgt: public Ui_GlViewSetingWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLVIEWSETINGWGT_H
