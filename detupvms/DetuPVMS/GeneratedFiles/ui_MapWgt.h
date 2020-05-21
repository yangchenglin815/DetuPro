/********************************************************************************
** Form generated from reading UI file 'MapWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPWGT_H
#define UI_MAPWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapWgt
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *mapSettingBtn;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *pathBuildingBtn;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *pathSaveBtn;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MapWgt)
    {
        if (MapWgt->objectName().isEmpty())
            MapWgt->setObjectName(QStringLiteral("MapWgt"));
        MapWgt->resize(870, 667);
        MapWgt->setStyleSheet(QString::fromUtf8("QToolButton,\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgb(255,255,255);\n"
"border-radius:15px;\n"
"}\n"
"#mapSettingBtn{\n"
"qproperty-icon:url(:/image/image/mapSet.png);\n"
"qproperty-iconSize:18px 18px;\n"
"padding-left:4px;\n"
"background:rgba(0,0,0,0.7);\n"
"}\n"
"#mapSettingBtn::hover{\n"
"border: 2px solid #8f8f91;\n"
"border-radius:15px;\n"
"}\n"
"#mapSettingBtn:pressed{\n"
"border-radius:14px;\n"
"margin:1px;\n"
"}\n"
"#pathBuildingBtn{\n"
"qproperty-icon:url(:/image/image/pathBuild.png);\n"
"qproperty-iconSize:18px 18px;\n"
"padding-left:4px;\n"
"background:rgba(0,0,0,0.7);\n"
"}\n"
"#pathBuildingBtn::hover{\n"
"border: 2px solid #8f8f91;\n"
"border-radius:15px;\n"
"}\n"
"#pathBuildingBtn:pressed{\n"
"border-radius:14px;\n"
"margin:1px;\n"
"}\n"
"\n"
"#pathSaveBtn{\n"
"qproperty-icon:url(:/image/image/savemap.png);\n"
"qproperty-iconSize:18px 18px;\n"
"padding-left:4px;\n"
"background:rgba(0,0,0,0.7);\n"
"}\n"
"#pathSaveBtn::"
                        "hover{\n"
"border: 2px solid #8f8f91;\n"
"border-radius:15px;\n"
"}\n"
"#pathSaveBtn:pressed{\n"
"border-radius:14px;\n"
"margin:1px;\n"
"}"));
        gridLayout = new QGridLayout(MapWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 6, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mapSettingBtn = new QToolButton(MapWgt);
        mapSettingBtn->setObjectName(QStringLiteral("mapSettingBtn"));
        mapSettingBtn->setMinimumSize(QSize(93, 30));
        mapSettingBtn->setMaximumSize(QSize(93, 30));
        mapSettingBtn->setIconSize(QSize(18, 18));
        mapSettingBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(mapSettingBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pathBuildingBtn = new QToolButton(MapWgt);
        pathBuildingBtn->setObjectName(QStringLiteral("pathBuildingBtn"));
        pathBuildingBtn->setMinimumSize(QSize(93, 30));
        pathBuildingBtn->setMaximumSize(QSize(93, 30));
        pathBuildingBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(pathBuildingBtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        pathSaveBtn = new QToolButton(MapWgt);
        pathSaveBtn->setObjectName(QStringLiteral("pathSaveBtn"));
        pathSaveBtn->setMinimumSize(QSize(93, 30));
        pathSaveBtn->setMaximumSize(QSize(93, 30));
        pathSaveBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout->addWidget(pathSaveBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 376, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);


        retranslateUi(MapWgt);

        QMetaObject::connectSlotsByName(MapWgt);
    } // setupUi

    void retranslateUi(QWidget *MapWgt)
    {
        MapWgt->setWindowTitle(QApplication::translate("MapWgt", "MapWgt", 0));
        mapSettingBtn->setText(QApplication::translate("MapWgt", "\350\256\276\347\275\256\345\234\260\345\233\276", 0));
        pathBuildingBtn->setText(QApplication::translate("MapWgt", "\347\224\237\346\210\220\350\267\257\345\276\204", 0));
        pathSaveBtn->setText(QApplication::translate("MapWgt", "\344\277\235\345\255\230\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class MapWgt: public Ui_MapWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPWGT_H
