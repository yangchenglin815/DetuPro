/********************************************************************************
** Form generated from reading UI file 'setTimeWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTIMEWIDGET_H
#define UI_SETTIMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setTimeWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QTimeEdit *timeEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *setTimeWidget)
    {
        if (setTimeWidget->objectName().isEmpty())
            setTimeWidget->setObjectName(QStringLiteral("setTimeWidget"));
        setTimeWidget->resize(107, 32);
        setTimeWidget->setMinimumSize(QSize(100, 32));
        setTimeWidget->setMaximumSize(QSize(107, 32));
        horizontalLayout = new QHBoxLayout(setTimeWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(setTimeWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 6, 9, 6);
        timeEdit = new QTimeEdit(widget);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setMinimumSize(QSize(0, 0));
        timeEdit->setAlignment(Qt::AlignCenter);
        timeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_2->addWidget(timeEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(16, 16));
        pushButton->setMaximumSize(QSize(16, 16));

        horizontalLayout_2->addWidget(pushButton);


        horizontalLayout->addWidget(widget);


        retranslateUi(setTimeWidget);

        QMetaObject::connectSlotsByName(setTimeWidget);
    } // setupUi

    void retranslateUi(QWidget *setTimeWidget)
    {
        setTimeWidget->setWindowTitle(QApplication::translate("setTimeWidget", "Form", 0));
        timeEdit->setDisplayFormat(QApplication::translate("setTimeWidget", "HH:mm:ss", 0));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class setTimeWidget: public Ui_setTimeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTIMEWIDGET_H
