/********************************************************************************
** Form generated from reading UI file 'paneWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANEWIDGET_H
#define UI_PANEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_paneWidget
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;

    void setupUi(QWidget *paneWidget)
    {
        if (paneWidget->objectName().isEmpty())
            paneWidget->setObjectName(QStringLiteral("paneWidget"));
        paneWidget->resize(200, 100);
        paneWidget->setMinimumSize(QSize(200, 100));
        paneWidget->setMaximumSize(QSize(200, 100));
        paneWidget->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:9px;\n"
"color:#121212;\n"
"background:#ffffff;\n"
"border:1px solid #ffffff;\n"
"border-radius:9px;\n"
"}\n"
"QPushButton:checked{\n"
"  background:#ffd500;\n"
"  border:1px solid #ffd500;\n"
"}\n"
"QPushButton:disabled\n"
"{\n"
"  background:rgb(203, 205, 204);\n"
"  border:1px solid rgb(203, 205, 204);\n"
"}\n"
"#widget{\n"
"border:1px solid #ffffff;\n"
"}\n"
""));
        gridLayout = new QGridLayout(paneWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(paneWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(18, 18));
        pushButton->setMaximumSize(QSize(18, 18));
        pushButton->setCheckable(true);

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(paneWidget);

        QMetaObject::connectSlotsByName(paneWidget);
    } // setupUi

    void retranslateUi(QWidget *paneWidget)
    {
        paneWidget->setWindowTitle(QApplication::translate("paneWidget", "Form", 0));
        pushButton->setText(QApplication::translate("paneWidget", "1", 0));
    } // retranslateUi

};

namespace Ui {
    class paneWidget: public Ui_paneWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANEWIDGET_H
