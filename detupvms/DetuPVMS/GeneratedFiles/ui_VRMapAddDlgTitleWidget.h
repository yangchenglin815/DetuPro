/********************************************************************************
** Form generated from reading UI file 'VRMapAddDlgTitleWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRMAPADDDLGTITLEWIDGET_H
#define UI_VRMAPADDDLGTITLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VRMapAddDlgTitleWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *VRMapAddDlgTitleWidget)
    {
        if (VRMapAddDlgTitleWidget->objectName().isEmpty())
            VRMapAddDlgTitleWidget->setObjectName(QStringLiteral("VRMapAddDlgTitleWidget"));
        VRMapAddDlgTitleWidget->resize(320, 30);
        VRMapAddDlgTitleWidget->setStyleSheet(QString::fromUtf8("QLabel,\n"
"QCheckBox{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:rgba(102,102,102,1);\n"
"}\n"
"#widget{\n"
"background:#ffffff;\n"
"border:1px solid #C3C9C9;\n"
"border-radius:0px;\n"
"}\n"
"#checkBox{\n"
"spacing:5px;\n"
"}\n"
"#checkBox::indicator{\n"
"  width: 18px;\n"
"  height:18px;\n"
"}\n"
"#checkBox::indicator:checked {\n"
"  image:url(:/image/image/addCheckboxb.png);\n"
"}\n"
"#checkBox::indicator:unchecked {\n"
"  image:url(:/image/image/addCheckbox.png);\n"
"}"));
        horizontalLayout = new QHBoxLayout(VRMapAddDlgTitleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(VRMapAddDlgTitleWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);


        horizontalLayout->addWidget(widget);


        retranslateUi(VRMapAddDlgTitleWidget);

        QMetaObject::connectSlotsByName(VRMapAddDlgTitleWidget);
    } // setupUi

    void retranslateUi(QWidget *VRMapAddDlgTitleWidget)
    {
        VRMapAddDlgTitleWidget->setWindowTitle(QApplication::translate("VRMapAddDlgTitleWidget", "VRMapAddDlgTitleWidget", 0));
        checkBox->setText(QApplication::translate("VRMapAddDlgTitleWidget", "\345\205\250\351\200\211", 0));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VRMapAddDlgTitleWidget: public Ui_VRMapAddDlgTitleWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRMAPADDDLGTITLEWIDGET_H
