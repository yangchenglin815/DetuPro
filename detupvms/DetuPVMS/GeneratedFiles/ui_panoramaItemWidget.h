/********************************************************************************
** Form generated from reading UI file 'panoramaItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PANORAMAITEMWIDGET_H
#define UI_PANORAMAITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_panoramaItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *iconLabel;
    QLabel *deviceLabel;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *panoramaItemWidget)
    {
        if (panoramaItemWidget->objectName().isEmpty())
            panoramaItemWidget->setObjectName(QStringLiteral("panoramaItemWidget"));
        panoramaItemWidget->resize(150, 42);
        panoramaItemWidget->setMinimumSize(QSize(150, 42));
        panoramaItemWidget->setMaximumSize(QSize(150, 42));
        panoramaItemWidget->setStyleSheet(QString::fromUtf8("#deviceLabel{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgba(238,238,238,1);\n"
"}\n"
"#widget{\n"
"background:rgba(24,25,25,1);\n"
"}\n"
"#label{\n"
"border-image:url(:/image/image/showNew.png);\n"
"}"));
        horizontalLayout = new QHBoxLayout(panoramaItemWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 3, 0, 3);
        widget = new QWidget(panoramaItemWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 36));
        widget->setMaximumSize(QSize(16777215, 36));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(12);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(15, 0, 0, 0);
        iconLabel = new QLabel(widget);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));
        iconLabel->setMinimumSize(QSize(18, 18));
        iconLabel->setMaximumSize(QSize(18, 18));

        horizontalLayout_2->addWidget(iconLabel);

        deviceLabel = new QLabel(widget);
        deviceLabel->setObjectName(QStringLiteral("deviceLabel"));

        horizontalLayout_2->addWidget(deviceLabel);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 1, -1, -1);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(24, 24));
        label->setMaximumSize(QSize(24, 24));

        verticalLayout->addWidget(label);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);


        horizontalLayout->addWidget(widget);


        retranslateUi(panoramaItemWidget);

        QMetaObject::connectSlotsByName(panoramaItemWidget);
    } // setupUi

    void retranslateUi(QWidget *panoramaItemWidget)
    {
        panoramaItemWidget->setWindowTitle(QApplication::translate("panoramaItemWidget", "Form", 0));
        iconLabel->setText(QString());
        deviceLabel->setText(QApplication::translate("panoramaItemWidget", "\345\205\250\346\231\257\347\233\270\346\234\272M1", 0));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class panoramaItemWidget: public Ui_panoramaItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PANORAMAITEMWIDGET_H
