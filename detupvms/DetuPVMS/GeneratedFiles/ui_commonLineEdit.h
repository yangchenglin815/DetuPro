/********************************************************************************
** Form generated from reading UI file 'commonLineEdit.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONLINEEDIT_H
#define UI_COMMONLINEEDIT_H

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

class Ui_commonLineEdit
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *commonLineEdit)
    {
        if (commonLineEdit->objectName().isEmpty())
            commonLineEdit->setObjectName(QStringLiteral("commonLineEdit"));
        commonLineEdit->resize(218, 27);
        commonLineEdit->setMinimumSize(QSize(0, 27));
        horizontalLayout = new QHBoxLayout(commonLineEdit);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(commonLineEdit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 0));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#ffffff;\n"
"border-radius: 2px;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, -1, 1);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 25));
        lineEdit->setStyleSheet(QString::fromUtf8("\n"
"border:none;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:1px;\n"
"text-align:justify;\n"
"\n"
"\n"
"\n"
"\n"
"\n"
""));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(14, 14));
        pushButton->setMaximumSize(QSize(14, 14));
        pushButton->setStyleSheet(QLatin1String("#pushButton{\n"
"  border-image:url(:/image/image/bubblex.png);\n"
"}\n"
"#pushButton:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(pushButton);


        horizontalLayout->addWidget(widget);


        retranslateUi(commonLineEdit);

        QMetaObject::connectSlotsByName(commonLineEdit);
    } // setupUi

    void retranslateUi(QWidget *commonLineEdit)
    {
        commonLineEdit->setWindowTitle(QApplication::translate("commonLineEdit", "commonLineEdit", 0));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class commonLineEdit: public Ui_commonLineEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONLINEEDIT_H
