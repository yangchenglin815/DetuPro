/********************************************************************************
** Form generated from reading UI file 'helpPageWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELPPAGEWIDGET_H
#define UI_HELPPAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "midarrowwidget.h"

QT_BEGIN_NAMESPACE

class Ui_helpPageWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    midArrowWidget *widget_;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *helpBtn;
    QFrame *line;
    QPushButton *aboutBtn;

    void setupUi(QWidget *helpPageWidget)
    {
        if (helpPageWidget->objectName().isEmpty())
            helpPageWidget->setObjectName(QStringLiteral("helpPageWidget"));
        helpPageWidget->resize(107, 69);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(helpPageWidget->sizePolicy().hasHeightForWidth());
        helpPageWidget->setSizePolicy(sizePolicy);
        helpPageWidget->setMinimumSize(QSize(0, 0));
        helpPageWidget->setMaximumSize(QSize(16777215, 16777215));
        helpPageWidget->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"background-color:#ffffff;\n"
"border-radius:5px;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"border:none;\n"
"text-align:left;\n"
"padding-left:10px;\n"
"}\n"
"QPushButton:hover{\n"
"background-color:#eeeeee;\n"
"}\n"
"Line{\n"
"background:#d8d8d8;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(helpPageWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_ = new midArrowWidget(helpPageWidget);
        widget_->setObjectName(QStringLiteral("widget_"));
        widget_->setMinimumSize(QSize(0, 8));
        widget_->setMaximumSize(QSize(16777215, 8));

        verticalLayout_2->addWidget(widget_);

        widget = new QWidget(helpPageWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        helpBtn = new QPushButton(widget);
        helpBtn->setObjectName(QStringLiteral("helpBtn"));
        sizePolicy.setHeightForWidth(helpBtn->sizePolicy().hasHeightForWidth());
        helpBtn->setSizePolicy(sizePolicy);
        helpBtn->setMinimumSize(QSize(0, 0));
        helpBtn->setMaximumSize(QSize(16777215, 16777215));
        helpBtn->setStyleSheet(QLatin1String("border-top-left-radius:5px;\n"
"border-top-right-radius:5px;"));

        verticalLayout->addWidget(helpBtn);

        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(105, 1));
        line->setMaximumSize(QSize(16777215, 1));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        aboutBtn = new QPushButton(widget);
        aboutBtn->setObjectName(QStringLiteral("aboutBtn"));
        sizePolicy.setHeightForWidth(aboutBtn->sizePolicy().hasHeightForWidth());
        aboutBtn->setSizePolicy(sizePolicy);
        aboutBtn->setMinimumSize(QSize(0, 0));
        aboutBtn->setMaximumSize(QSize(16777215, 16777215));
        aboutBtn->setStyleSheet(QLatin1String("border-bottom-left-radius:5px;\n"
"border-bottom-right-radius:5px;"));

        verticalLayout->addWidget(aboutBtn);


        verticalLayout_2->addWidget(widget);


        retranslateUi(helpPageWidget);

        QMetaObject::connectSlotsByName(helpPageWidget);
    } // setupUi

    void retranslateUi(QWidget *helpPageWidget)
    {
        helpPageWidget->setWindowTitle(QApplication::translate("helpPageWidget", "Form", 0));
        helpBtn->setText(QApplication::translate("helpPageWidget", "\345\270\256\345\212\251\346\211\213\345\206\214", 0));
        aboutBtn->setText(QApplication::translate("helpPageWidget", "\345\205\263\344\272\216", 0));
    } // retranslateUi

};

namespace Ui {
    class helpPageWidget: public Ui_helpPageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELPPAGEWIDGET_H
