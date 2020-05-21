/********************************************************************************
** Form generated from reading UI file 'consoletabwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLETABWIDGET_H
#define UI_CONSOLETABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_consoleTabWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *logo;
    QLabel *label;

    void setupUi(QWidget *consoleTabWidget)
    {
        if (consoleTabWidget->objectName().isEmpty())
            consoleTabWidget->setObjectName(QStringLiteral("consoleTabWidget"));
        consoleTabWidget->setWindowModality(Qt::NonModal);
        consoleTabWidget->resize(94, 30);
        consoleTabWidget->setMinimumSize(QSize(83, 30));
        consoleTabWidget->setMaximumSize(QSize(16777215, 35));
        horizontalLayout = new QHBoxLayout(consoleTabWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(consoleTabWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#2a2b2b;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(17, 0, 9, 0);
        logo = new QLabel(widget);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setMinimumSize(QSize(13, 12));
        logo->setMaximumSize(QSize(13, 12));
        logo->setStyleSheet(QLatin1String("#logo{\n"
"background-image:url(:/image/image/console.png);\n"
"}"));

        horizontalLayout_2->addWidget(logo);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(36, 14));
        label->setMaximumSize(QSize(36, 14));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#eeeeee;\n"
"text-align:left;\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);


        horizontalLayout->addWidget(widget);


        retranslateUi(consoleTabWidget);

        QMetaObject::connectSlotsByName(consoleTabWidget);
    } // setupUi

    void retranslateUi(QWidget *consoleTabWidget)
    {
        consoleTabWidget->setWindowTitle(QApplication::translate("consoleTabWidget", "Form", 0));
        logo->setText(QString());
        label->setText(QApplication::translate("consoleTabWidget", "\346\216\247\345\210\266\345\217\260", 0));
    } // retranslateUi

};

namespace Ui {
    class consoleTabWidget: public Ui_consoleTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLETABWIDGET_H
