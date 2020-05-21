/********************************************************************************
** Form generated from reading UI file 'speedControlWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPEEDCONTROLWIDGET_H
#define UI_SPEEDCONTROLWIDGET_H

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

class Ui_speedControlWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QPushButton *slowBtn;
    QLabel *label;
    QPushButton *fastBtn;

    void setupUi(QWidget *speedControlWidget)
    {
        if (speedControlWidget->objectName().isEmpty())
            speedControlWidget->setObjectName(QStringLiteral("speedControlWidget"));
        speedControlWidget->resize(121, 32);
        speedControlWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#A4A6A6;\n"
"padding-left:1px;\n"
"}\n"
"#widget{\n"
"border: 1px solid #868989;\n"
"/*border-radius:15px;*/\n"
"}"));
        horizontalLayout = new QHBoxLayout(speedControlWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        slowBtn = new QPushButton(speedControlWidget);
        slowBtn->setObjectName(QStringLiteral("slowBtn"));
        slowBtn->setMinimumSize(QSize(36, 32));
        slowBtn->setMaximumSize(QSize(36, 32));
        slowBtn->setStyleSheet(QLatin1String("#slowBtn{\n"
"background-image:url(:/image/image/slow.png);\n"
"background-size:12px 12px;\n"
"background-repeat:no-repeat;\n"
"background-position:center;\n"
"background-color:#1f2020;\n"
"border: 1px solid #868989;\n"
"border-right:none;\n"
"border-top-left-radius:15px;\n"
"border-bottom-left-radius:15px;\n"
"}\n"
"#slowBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#slowBtn:hover{\n"
"background-image:url(:/image/image/slowb.png);\n"
"background-size:12px 12px;\n"
"background-repeat:no-repeat;\n"
"background-position:center;\n"
"background-color:#4E5050;\n"
"}"));

        horizontalLayout->addWidget(slowBtn);

        label = new QLabel(speedControlWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QLatin1String("border: 1px solid #868989;\n"
"border-left:none;\n"
"border-right:none;"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        fastBtn = new QPushButton(speedControlWidget);
        fastBtn->setObjectName(QStringLiteral("fastBtn"));
        fastBtn->setMinimumSize(QSize(36, 32));
        fastBtn->setMaximumSize(QSize(36, 32));
        fastBtn->setStyleSheet(QLatin1String("#fastBtn{\n"
"background-image:url(:/image/image/fast.png);\n"
"background-size:12px 12px;\n"
"background-repeat:no-repeat;\n"
"background-position:center;\n"
"background-color:#1f2020;\n"
"border: 1px solid #868989;\n"
"border-left:none;\n"
"border-top-right-radius:15px;\n"
"border-bottom-right-radius:15px;\n"
"}\n"
"#fastBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#fastBtn:hover{\n"
"background-image:url(:/image/image/fastb.png);\n"
"background-size:12px 12px;\n"
"background-repeat:no-repeat;\n"
"background-position:center;\n"
"background-color:#4E5050;\n"
"}"));

        horizontalLayout->addWidget(fastBtn);


        retranslateUi(speedControlWidget);

        QMetaObject::connectSlotsByName(speedControlWidget);
    } // setupUi

    void retranslateUi(QWidget *speedControlWidget)
    {
        speedControlWidget->setWindowTitle(QApplication::translate("speedControlWidget", "Form", 0));
        slowBtn->setText(QString());
        label->setText(QApplication::translate("speedControlWidget", "1/16 X", 0));
        fastBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class speedControlWidget: public Ui_speedControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPEEDCONTROLWIDGET_H
