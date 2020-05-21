/********************************************************************************
** Form generated from reading UI file 'setDateWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDATEWIDGET_H
#define UI_SETDATEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setDateWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *dateBtn;

    void setupUi(QWidget *setDateWidget)
    {
        if (setDateWidget->objectName().isEmpty())
            setDateWidget->setObjectName(QStringLiteral("setDateWidget"));
        setDateWidget->resize(92, 33);
        horizontalLayout = new QHBoxLayout(setDateWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(setDateWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(70, 0));
        lineEdit->setMaximumSize(QSize(70, 16777215));
        lineEdit->setFrame(false);

        horizontalLayout_2->addWidget(lineEdit);

        dateBtn = new QPushButton(widget);
        dateBtn->setObjectName(QStringLiteral("dateBtn"));
        dateBtn->setMinimumSize(QSize(16, 16));
        dateBtn->setMaximumSize(QSize(16, 16));
        dateBtn->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(dateBtn);


        horizontalLayout->addWidget(widget);


        retranslateUi(setDateWidget);

        QMetaObject::connectSlotsByName(setDateWidget);
    } // setupUi

    void retranslateUi(QWidget *setDateWidget)
    {
        setDateWidget->setWindowTitle(QApplication::translate("setDateWidget", "Form", 0));
        lineEdit->setText(QApplication::translate("setDateWidget", "2017-06-08", 0));
        dateBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class setDateWidget: public Ui_setDateWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDATEWIDGET_H
