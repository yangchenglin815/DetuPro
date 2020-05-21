/********************************************************************************
** Form generated from reading UI file 'DetuPVMS.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETUPVMS_H
#define UI_DETUPVMS_H

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
#include "detutittlewgt.h"
#include "homewgt.h"

QT_BEGIN_NAMESPACE

class Ui_DetuPVMS
{
public:
    QVBoxLayout *verticalLayout;
    detuTittleWgt *tittleWidget;
    homeWgt *homeWidget;
    QWidget *bottomWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLabel *flvTag;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *label_2;

    void setupUi(QWidget *DetuPVMS)
    {
        if (DetuPVMS->objectName().isEmpty())
            DetuPVMS->setObjectName(QStringLiteral("DetuPVMS"));
        DetuPVMS->resize(1200, 660);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DetuPVMS->sizePolicy().hasHeightForWidth());
        DetuPVMS->setSizePolicy(sizePolicy);
        DetuPVMS->setMinimumSize(QSize(1200, 660));
        DetuPVMS->setStyleSheet(QLatin1String("#bottomWidget{\n"
"background:#1f2020;\n"
"border-top:1px solid #121212;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DetuPVMS);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tittleWidget = new detuTittleWgt(DetuPVMS);
        tittleWidget->setObjectName(QStringLiteral("tittleWidget"));
        tittleWidget->setMinimumSize(QSize(0, 36));
        tittleWidget->setMaximumSize(QSize(16777215, 36));
        tittleWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(tittleWidget);

        homeWidget = new homeWgt(DetuPVMS);
        homeWidget->setObjectName(QStringLiteral("homeWidget"));
        homeWidget->setMinimumSize(QSize(0, 0));
        homeWidget->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(homeWidget);

        bottomWidget = new QWidget(DetuPVMS);
        bottomWidget->setObjectName(QStringLiteral("bottomWidget"));
        bottomWidget->setMinimumSize(QSize(0, 30));
        bottomWidget->setMaximumSize(QSize(16777215, 30));
        bottomWidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(bottomWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(20, 0, 10, 0);
        label = new QLabel(bottomWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#CCCCCC;\n"
""));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_4 = new QLabel(bottomWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:white;"));

        horizontalLayout->addWidget(label_4);

        flvTag = new QLabel(bottomWidget);
        flvTag->setObjectName(QStringLiteral("flvTag"));
        flvTag->setMinimumSize(QSize(10, 10));
        flvTag->setMaximumSize(QSize(10, 10));

        horizontalLayout->addWidget(flvTag);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_3 = new QLabel(bottomWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:white;"));

        horizontalLayout->addWidget(label_3, 0, Qt::AlignHCenter);

        label_2 = new QLabel(bottomWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(10, 10));
        label_2->setMaximumSize(QSize(10, 10));
        label_2->setStyleSheet(QStringLiteral(""));

        horizontalLayout->addWidget(label_2);


        verticalLayout->addWidget(bottomWidget);


        retranslateUi(DetuPVMS);

        QMetaObject::connectSlotsByName(DetuPVMS);
    } // setupUi

    void retranslateUi(QWidget *DetuPVMS)
    {
        DetuPVMS->setWindowTitle(QApplication::translate("DetuPVMS", "Form", 0));
        label->setText(QString());
        label_4->setText(QApplication::translate("DetuPVMS", "\345\275\225\346\265\201\347\212\266\346\200\201\357\274\232 ", 0));
        flvTag->setText(QString());
        label_3->setText(QApplication::translate("DetuPVMS", "\346\234\215\345\212\241\345\231\250\357\274\232 ", 0));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DetuPVMS: public Ui_DetuPVMS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETUPVMS_H
