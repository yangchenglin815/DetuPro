/********************************************************************************
** Form generated from reading UI file 'commonPageWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONPAGEWGT_H
#define UI_COMMONPAGEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commonPageWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QLabel *tittleLabel_;
    QLabel *contentLabel_;

    void setupUi(QWidget *commonPageWgt)
    {
        if (commonPageWgt->objectName().isEmpty())
            commonPageWgt->setObjectName(QStringLiteral("commonPageWgt"));
        commonPageWgt->resize(325, 126);
        commonPageWgt->setMinimumSize(QSize(325, 126));
        horizontalLayout = new QHBoxLayout(commonPageWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(commonPageWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"border-radius:3px;\n"
"}\n"
"#widget:hover{\n"
"background:rgba(255,255,255,0.02);\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(30, 30, 28, 34);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(64, 64));
        label->setMaximumSize(QSize(64, 64));
        label->setStyleSheet(QStringLiteral(""));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tittleLabel_ = new QLabel(widget_2);
        tittleLabel_->setObjectName(QStringLiteral("tittleLabel_"));
        tittleLabel_->setMinimumSize(QSize(108, 20));
        tittleLabel_->setMaximumSize(QSize(108, 20));
        tittleLabel_->setStyleSheet(QString::fromUtf8("#tittleLabel_{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:16px;\n"
"color:#eeeeee;\n"
"line-height:20px;\n"
"text-align:left;\n"
"}\n"
""));

        verticalLayout->addWidget(tittleLabel_);

        contentLabel_ = new QLabel(widget_2);
        contentLabel_->setObjectName(QStringLiteral("contentLabel_"));
        contentLabel_->setMinimumSize(QSize(183, 36));
        contentLabel_->setMaximumSize(QSize(183, 36));
        contentLabel_->setStyleSheet(QString::fromUtf8("#contentLabel_{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:18px;\n"
"text-align:left;\n"
"}"));
        contentLabel_->setWordWrap(true);

        verticalLayout->addWidget(contentLabel_);


        horizontalLayout_2->addWidget(widget_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(commonPageWgt);

        QMetaObject::connectSlotsByName(commonPageWgt);
    } // setupUi

    void retranslateUi(QWidget *commonPageWgt)
    {
        commonPageWgt->setWindowTitle(QApplication::translate("commonPageWgt", "Form", 0));
        label->setText(QString());
        tittleLabel_->setText(QApplication::translate("commonPageWgt", "\345\255\230\345\202\250\350\256\241\345\210\222", 0));
        contentLabel_->setText(QApplication::translate("commonPageWgt", "<html><head/><body><p>\346\214\207\345\256\232\346\212\223\345\233\276\346\210\226\345\275\225\345\203\217\347\232\204\350\216\267\345\217\226\350\247\204\345\210\231\357\274\214\351\205\215</p><p>\347\275\256\345\255\230\345\202\250\350\267\257\345\276\204</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class commonPageWgt: public Ui_commonPageWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONPAGEWGT_H
