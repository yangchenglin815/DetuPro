/********************************************************************************
** Form generated from reading UI file 'commonButton.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONBUTTON_H
#define UI_COMMONBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commonButton
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *iconLabel;
    QLabel *textLabel;

    void setupUi(QWidget *commonButton)
    {
        if (commonButton->objectName().isEmpty())
            commonButton->setObjectName(QStringLiteral("commonButton"));
        commonButton->resize(93, 32);
        commonButton->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(commonButton);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(commonButton);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(12, 0, -1, 0);
        iconLabel = new QLabel(widget);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));

        horizontalLayout->addWidget(iconLabel);

        textLabel = new QLabel(widget);
        textLabel->setObjectName(QStringLiteral("textLabel"));

        horizontalLayout->addWidget(textLabel);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(commonButton);

        QMetaObject::connectSlotsByName(commonButton);
    } // setupUi

    void retranslateUi(QWidget *commonButton)
    {
        commonButton->setWindowTitle(QApplication::translate("commonButton", "Form", 0));
        iconLabel->setText(QString());
        textLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class commonButton: public Ui_commonButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONBUTTON_H
