/********************************************************************************
** Form generated from reading UI file 'dlg_titleWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_TITLEWGT_H
#define UI_DLG_TITLEWGT_H

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

class Ui_dlg_titleWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeBtn;

    void setupUi(QWidget *dlg_titleWgt)
    {
        if (dlg_titleWgt->objectName().isEmpty())
            dlg_titleWgt->setObjectName(QStringLiteral("dlg_titleWgt"));
        dlg_titleWgt->resize(493, 41);
        dlg_titleWgt->setMinimumSize(QSize(0, 41));
        dlg_titleWgt->setMaximumSize(QSize(16777215, 41));
        horizontalLayout = new QHBoxLayout(dlg_titleWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(dlg_titleWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"  \n"
"	background-color: rgb(255, 255, 255);\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"text-align:center;\n"
"}"));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        closeBtn = new QPushButton(widget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(10, 10));
        closeBtn->setMaximumSize(QSize(10, 10));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
" border-image:url(:/image/image/popupx2.png);\n"
"}\n"
"#closeBtn:hover{\n"
" border-image:url(:/image/image/popupx2b.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(closeBtn);


        horizontalLayout->addWidget(widget);


        retranslateUi(dlg_titleWgt);

        QMetaObject::connectSlotsByName(dlg_titleWgt);
    } // setupUi

    void retranslateUi(QWidget *dlg_titleWgt)
    {
        dlg_titleWgt->setWindowTitle(QApplication::translate("dlg_titleWgt", "Form", 0));
        label->setText(QApplication::translate("dlg_titleWgt", "\346\240\207\351\242\230", 0));
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class dlg_titleWgt: public Ui_dlg_titleWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_TITLEWGT_H
