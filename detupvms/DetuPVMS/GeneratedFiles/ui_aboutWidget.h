/********************************************************************************
** Form generated from reading UI file 'aboutWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWIDGET_H
#define UI_ABOUTWIDGET_H

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

class Ui_aboutWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *nameLabel;
    QSpacerItem *verticalSpacer_2;
    QLabel *versionLabel;
    QSpacerItem *verticalSpacer_3;
    QLabel *urlLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *aboutWidget)
    {
        if (aboutWidget->objectName().isEmpty())
            aboutWidget->setObjectName(QStringLiteral("aboutWidget"));
        aboutWidget->resize(521, 298);
        aboutWidget->setStyleSheet(QLatin1String("QWidget#widget{\n"
"background:#eeeeee;\n"
"box-shadow:0 2px 10px 1px rgba(0,0,0,0.20);\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"\n"
"}"));
        horizontalLayout = new QHBoxLayout(aboutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(aboutWidget);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, 0);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 50, 0, 0);
        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(96, 96));
        label->setMaximumSize(QSize(96, 96));
        label->setStyleSheet(QStringLiteral("border-image:url(:/image/image/about.png);"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer = new QSpacerItem(11, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(widget_2);

        verticalSpacer = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        nameLabel = new QLabel(widget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setMinimumSize(QSize(123, 20));
        nameLabel->setMaximumSize(QSize(123, 20));
        nameLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:16px;\n"
"color:#333333;\n"
"line-height:20px;\n"
"text-align:right;"));
        nameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nameLabel, 0, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 8, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        versionLabel = new QLabel(widget);
        versionLabel->setObjectName(QStringLiteral("versionLabel"));
        versionLabel->setMinimumSize(QSize(123, 14));
        versionLabel->setMaximumSize(QSize(123, 14));
        versionLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"text-align:center;"));
        versionLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(versionLabel, 0, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        urlLabel = new QLabel(widget);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(urlLabel->sizePolicy().hasHeightForWidth());
        urlLabel->setSizePolicy(sizePolicy);
        urlLabel->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:13px;\n"
"color:#666666;\n"
"text-align:center;\n"
""));
        urlLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(urlLabel, 0, Qt::AlignHCenter);

        verticalSpacer_4 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_4);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(0, 0));
        label_2->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:13px;\n"
"color:#666666;"));

        verticalLayout->addWidget(label_2, 0, Qt::AlignHCenter);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);


        horizontalLayout->addWidget(widget);


        retranslateUi(aboutWidget);

        QMetaObject::connectSlotsByName(aboutWidget);
    } // setupUi

    void retranslateUi(QWidget *aboutWidget)
    {
        aboutWidget->setWindowTitle(QApplication::translate("aboutWidget", "Form", 0));
        label->setText(QString());
        nameLabel->setText(QApplication::translate("aboutWidget", "Pano-VMS", 0));
        versionLabel->setText(QString());
        urlLabel->setText(QString());
        label_2->setText(QApplication::translate("aboutWidget", "\302\251 2017 detu All rights reseved", 0));
    } // retranslateUi

};

namespace Ui {
    class aboutWidget: public Ui_aboutWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWIDGET_H
