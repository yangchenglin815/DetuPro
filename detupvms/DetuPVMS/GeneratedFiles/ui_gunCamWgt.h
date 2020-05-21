/********************************************************************************
** Form generated from reading UI file 'gunCamWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUNCAMWGT_H
#define UI_GUNCAMWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gunCamWgt
{
public:
    QGridLayout *gridLayout_2;
    QWidget *titleWidget;
    QGridLayout *gridLayout;
    QLabel *titleLabel;
    QPushButton *closeBtn;
    QPushButton *scaleBtn;
    QWidget *midWidget;
    QGridLayout *gridLayout_4;
    QWidget *widget;
    QGridLayout *gridLayout_3;

    void setupUi(QWidget *gunCamWgt)
    {
        if (gunCamWgt->objectName().isEmpty())
            gunCamWgt->setObjectName(QStringLiteral("gunCamWgt"));
        gunCamWgt->resize(834, 523);
        gunCamWgt->setStyleSheet(QString::fromUtf8("#gunCamWgt{\n"
"background:transparent;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#midWidget{\n"
"background:#eeeeee;\n"
"}\n"
"#bottomWidget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));
        gridLayout_2 = new QGridLayout(gunCamWgt);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(gunCamWgt);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        gridLayout = new QGridLayout(titleWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, 0);
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy);
        titleLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(titleLabel, 0, 0, 1, 1);

        closeBtn = new QPushButton(titleWidget);
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

        gridLayout->addWidget(closeBtn, 0, 2, 1, 1);

        scaleBtn = new QPushButton(titleWidget);
        scaleBtn->setObjectName(QStringLiteral("scaleBtn"));
        scaleBtn->setMinimumSize(QSize(10, 10));
        scaleBtn->setMaximumSize(QSize(10, 10));
        scaleBtn->setStyleSheet(QLatin1String("#scaleBtn{\n"
" border-image:url(:/image/image/windowbigerb.png);\n"
"}\n"
"#scaleBtn:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(scaleBtn, 0, 1, 1, 1);


        gridLayout_2->addWidget(titleWidget, 0, 0, 1, 1);

        midWidget = new QWidget(gunCamWgt);
        midWidget->setObjectName(QStringLiteral("midWidget"));
        sizePolicy.setHeightForWidth(midWidget->sizePolicy().hasHeightForWidth());
        midWidget->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(midWidget);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(midWidget);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(600, 400));
        widget->setMaximumSize(QSize(666666, 666666));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);

        gridLayout_4->addWidget(widget, 0, 0, 1, 1);


        gridLayout_2->addWidget(midWidget, 1, 0, 1, 1);


        retranslateUi(gunCamWgt);

        QMetaObject::connectSlotsByName(gunCamWgt);
    } // setupUi

    void retranslateUi(QWidget *gunCamWgt)
    {
        gunCamWgt->setWindowTitle(QApplication::translate("gunCamWgt", "gunCamWgt", 0));
        titleLabel->setText(QApplication::translate("gunCamWgt", "\347\220\203\346\234\272192.168.2.110", 0));
        closeBtn->setText(QString());
        scaleBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gunCamWgt: public Ui_gunCamWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUNCAMWGT_H
