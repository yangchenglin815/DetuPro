/********************************************************************************
** Form generated from reading UI file 'durationWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DURATIONWIDGET_H
#define UI_DURATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_durationWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *decreaseBtn;
    QSlider *horizontalSlider;
    QPushButton *addBtn;

    void setupUi(QWidget *durationWidget)
    {
        if (durationWidget->objectName().isEmpty())
            durationWidget->setObjectName(QStringLiteral("durationWidget"));
        durationWidget->resize(160, 20);
        durationWidget->setMinimumSize(QSize(0, 20));
        durationWidget->setMaximumSize(QSize(168, 20));
        durationWidget->setStyleSheet(QLatin1String("#widget{\n"
"background-color:#1f2020;\n"
"border:1px solid #121212;\n"
"border-top:none;\n"
"border-bottom:none;\n"
"border-right:none;\n"
"}\n"
"\n"
""));
        horizontalLayout_2 = new QHBoxLayout(durationWidget);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(durationWidget);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        decreaseBtn = new QPushButton(widget);
        decreaseBtn->setObjectName(QStringLiteral("decreaseBtn"));
        decreaseBtn->setMinimumSize(QSize(20, 20));
        decreaseBtn->setMaximumSize(QSize(20, 20));
        decreaseBtn->setStyleSheet(QLatin1String("#decreaseBtn{\n"
"border-image: url(:/image/image/decrease.png);\n"
"}\n"
"#decreaseBtn:hover{\n"
"border-image: url(:/image/image/decreaseb.png);\n"
"}\n"
"#decreaseBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""));

        horizontalLayout->addWidget(decreaseBtn);

        horizontalSlider = new QSlider(widget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMinimumSize(QSize(80, 20));
        horizontalSlider->setStyleSheet(QLatin1String("QSlider{\n"
"height:28px;\n"
"	background:#1f2020;\n"
"/*border:1px solid #121212;\n"
"border-top:none;\n"
"border-left:none;\n"
"border-right:none;*/\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"     	border: 0px solid #212121;\n"
"     	height: 2px;\n"
"    	background: #4e5050;\n"
"        left:7px;\n"
"        right:7px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {		 \n"
"		 border-image: url(:/image/image/volume_btn.png);\n"
"   		 background: transparent;\n"
"   		 width: 12px;\n"
"		 height: 12px;\n"
"         margin-top:-5px;\n"
"		 margin-bottom:-5px;\n"
"         margin-left:-7px;\n"
"		 margin-right:-7px;\n"
"}\n"
"\n"
"QSlider#volume_slider_::add-page::horizontal{\n"
"        background: #4e5050;\n"
"}\n"
"\n"
"QSlider#volume_slider_::sub-page::horizontal{\n"
"        background: #ffd500;\n"
"}"));
        horizontalSlider->setMaximum(99);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        addBtn = new QPushButton(widget);
        addBtn->setObjectName(QStringLiteral("addBtn"));
        addBtn->setMinimumSize(QSize(20, 20));
        addBtn->setMaximumSize(QSize(20, 20));
        addBtn->setStyleSheet(QLatin1String("#addBtn{\n"
"border-image: url(:/image/image/increase.png);\n"
"}\n"
"#addBtn:hover{\n"
"border-image: url(:/image/image/increaseb.png);\n"
"}\n"
"#addBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout->addWidget(addBtn);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(durationWidget);

        QMetaObject::connectSlotsByName(durationWidget);
    } // setupUi

    void retranslateUi(QWidget *durationWidget)
    {
        durationWidget->setWindowTitle(QApplication::translate("durationWidget", "Form", 0));
        decreaseBtn->setText(QString());
        addBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class durationWidget: public Ui_durationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DURATIONWIDGET_H
