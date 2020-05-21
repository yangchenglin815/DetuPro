/********************************************************************************
** Form generated from reading UI file 'selectedItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTEDITEMWIDGET_H
#define UI_SELECTEDITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selectedItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QLabel *ipLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *portLabel;

    void setupUi(QWidget *selectedItemWidget)
    {
        if (selectedItemWidget->objectName().isEmpty())
            selectedItemWidget->setObjectName(QStringLiteral("selectedItemWidget"));
        selectedItemWidget->resize(320, 30);
        selectedItemWidget->setStyleSheet(QString::fromUtf8("\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#666666;\n"
"border:none;\n"
"}\n"
"#pushButton{\n"
"border-image:url(:/image/image/radio_off.png);\n"
"}\n"
"#pushButton:checked{\n"
"border-image:url(:/image/image/radio_on.png);\n"
"}"));
        horizontalLayout = new QHBoxLayout(selectedItemWidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 0, 40, 0);
        pushButton = new QPushButton(selectedItemWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(12, 12));
        pushButton->setMaximumSize(QSize(12, 12));
        pushButton->setCheckable(true);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ipLabel = new QLabel(selectedItemWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(ipLabel, 0, Qt::AlignHCenter);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        portLabel = new QLabel(selectedItemWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));

        horizontalLayout->addWidget(portLabel, 0, Qt::AlignHCenter);


        retranslateUi(selectedItemWidget);

        QMetaObject::connectSlotsByName(selectedItemWidget);
    } // setupUi

    void retranslateUi(QWidget *selectedItemWidget)
    {
        selectedItemWidget->setWindowTitle(QApplication::translate("selectedItemWidget", "Form", 0));
        pushButton->setText(QString());
        ipLabel->setText(QApplication::translate("selectedItemWidget", "192.168.100.1", 0));
        portLabel->setText(QApplication::translate("selectedItemWidget", "8088", 0));
    } // retranslateUi

};

namespace Ui {
    class selectedItemWidget: public Ui_selectedItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTEDITEMWIDGET_H
