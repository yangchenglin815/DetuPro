/********************************************************************************
** Form generated from reading UI file 'suptabwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUPTABWIDGET_H
#define UI_SUPTABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_supTabWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *closeBtn;

    void setupUi(QWidget *supTabWidget)
    {
        if (supTabWidget->objectName().isEmpty())
            supTabWidget->setObjectName(QStringLiteral("supTabWidget"));
        supTabWidget->resize(94, 31);
        supTabWidget->setStyleSheet(QString::fromUtf8("#label{\n"
"    font:12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(supTabWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(supTabWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#323232;\n"
"border:1px solid #000000;\n"
"}"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 9, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(24, 14));
        label->setMaximumSize(QSize(16777215, 14));
        label->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#eeeeee;\n"
"text-align:left;"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(8, 8));
        closeBtn->setMaximumSize(QSize(8, 8));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
"border-image:url(:/image/image/popupx.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout->addWidget(closeBtn);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(supTabWidget);

        QMetaObject::connectSlotsByName(supTabWidget);
    } // setupUi

    void retranslateUi(QWidget *supTabWidget)
    {
        supTabWidget->setWindowTitle(QApplication::translate("supTabWidget", "Form", 0));
        label->setText(QApplication::translate("supTabWidget", "\351\242\204\350\247\210", 0));
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class supTabWidget: public Ui_supTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUPTABWIDGET_H
