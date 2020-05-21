/********************************************************************************
** Form generated from reading UI file 'MapPointWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPPOINTWGT_H
#define UI_MAPPOINTWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapPointWgt
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *MapPointWgt)
    {
        if (MapPointWgt->objectName().isEmpty())
            MapPointWgt->setObjectName(QStringLiteral("MapPointWgt"));
        MapPointWgt->resize(93, 128);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MapPointWgt->sizePolicy().hasHeightForWidth());
        MapPointWgt->setSizePolicy(sizePolicy);
        MapPointWgt->setMinimumSize(QSize(93, 128));
        MapPointWgt->setMaximumSize(QSize(93, 128));
        MapPointWgt->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(MapPointWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(MapPointWgt);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(93, 30));
        label->setMaximumSize(QSize(93, 30));
        label->setStyleSheet(QString::fromUtf8("#label{\n"
"background-color:rgba(0,0,0,0.7);\n"
"border-radius:15px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgba(255,255,255,1);\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        label_2 = new QLabel(MapPointWgt);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(45, 98));
        label_2->setMaximumSize(QSize(45, 98));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(21, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 1);


        retranslateUi(MapPointWgt);

        QMetaObject::connectSlotsByName(MapPointWgt);
    } // setupUi

    void retranslateUi(QWidget *MapPointWgt)
    {
        MapPointWgt->setWindowTitle(QApplication::translate("MapPointWgt", "MapPointWgt", 0));
        label->setText(QString());
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MapPointWgt: public Ui_MapPointWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPOINTWGT_H
