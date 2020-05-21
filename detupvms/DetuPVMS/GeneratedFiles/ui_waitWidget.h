/********************************************************************************
** Form generated from reading UI file 'waitWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAITWIDGET_H
#define UI_WAITWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_waitWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;

    void setupUi(QWidget *waitWidget)
    {
        if (waitWidget->objectName().isEmpty())
            waitWidget->setObjectName(QStringLiteral("waitWidget"));
        waitWidget->resize(303, 44);
        horizontalLayout = new QHBoxLayout(waitWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(waitWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"	background-color: rgb(255, 255, 255);\n"
"border-radius:4px;\n"
"\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"text-align:center;"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        horizontalLayout->addWidget(widget);


        retranslateUi(waitWidget);

        QMetaObject::connectSlotsByName(waitWidget);
    } // setupUi

    void retranslateUi(QWidget *waitWidget)
    {
        waitWidget->setWindowTitle(QApplication::translate("waitWidget", "Form", 0));
        label->setText(QApplication::translate("waitWidget", "\346\255\243\345\234\250\346\240\274\345\274\217\345\214\226...", 0));
    } // retranslateUi

};

namespace Ui {
    class waitWidget: public Ui_waitWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAITWIDGET_H
