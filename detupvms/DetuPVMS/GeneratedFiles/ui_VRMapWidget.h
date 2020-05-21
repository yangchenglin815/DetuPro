/********************************************************************************
** Form generated from reading UI file 'VRMapWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VRMAPWIDGET_H
#define UI_VRMAPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MapWgt.h"
#include "commonListWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VRMapWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *leftWidget;
    QVBoxLayout *verticalLayout;
    QToolButton *addPanoramaBtn;
    QFrame *line;
    commonListWidget *listWidget;
    QWidget *rightWidget;
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *initPage;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QPushButton *addMapBtn;
    QSpacerItem *horizontalSpacer_2;
    MapWgt *mapPage;

    void setupUi(QWidget *VRMapWidget)
    {
        if (VRMapWidget->objectName().isEmpty())
            VRMapWidget->setObjectName(QStringLiteral("VRMapWidget"));
        VRMapWidget->resize(1016, 633);
        VRMapWidget->setStyleSheet(QString::fromUtf8("#leftWidget{\n"
"background-color:#1f2020;\n"
"border-right:1px solid #111111;\n"
"}\n"
"#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:left;\n"
"}\n"
"#line{\n"
"background:#444444;\n"
"}\n"
"#listWidget{\n"
"background-color:#1f2020;\n"
"border:none;\n"
"}\n"
"QListView::item{\n"
"padding-left:15px;\n"
"}\n"
"QListView::item:hover{\n"
"/*border:1px solid #00A092;*/\n"
"}\n"
"QToolButton,\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgb(255,255,255);\n"
"border-radius:15px;\n"
"background:rgba(0,0,0,0.7);\n"
"}\n"
"#mapSettingBtn{\n"
"qproperty-icon:url(:/image/image/mapSet.png);\n"
"qproperty-iconSize:18px 18px;\n"
"padding-left:4px;\n"
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
"qpropert"
                        "y-icon:url(:/image/image/pathBuild.png);\n"
"qproperty-iconSize:18px 18px;\n"
"padding-left:4px;\n"
"}\n"
"#pathBuildingBtn::hover{\n"
"border: 2px solid #8f8f91;\n"
"border-radius:15px;\n"
"}\n"
"#pathBuildingBtn:pressed{\n"
"border-radius:14px;\n"
"margin:1px;\n"
"}\n"
"#addPanoramaBtn::hover{\n"
"color:#FFD500;\n"
"}\n"
"#initPage{\n"
"background-color:#1f2020;\n"
"}\n"
"#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:rgba(238,238,238,1);\n"
"}\n"
"#addMapBtn{\n"
"border-radius:14px;\n"
"border-image:url(:/image/image/addMap.png);\n"
"}\n"
"#addMapBtn::hover{\n"
"border-image:url(:/image/image/addMaph.png);\n"
"}"));
        horizontalLayout = new QHBoxLayout(VRMapWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leftWidget = new QWidget(VRMapWidget);
        leftWidget->setObjectName(QStringLiteral("leftWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leftWidget->sizePolicy().hasHeightForWidth());
        leftWidget->setSizePolicy(sizePolicy);
        leftWidget->setMinimumSize(QSize(190, 0));
        leftWidget->setMaximumSize(QSize(190, 16777215));
        verticalLayout = new QVBoxLayout(leftWidget);
        verticalLayout->setSpacing(15);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(6, 18, 6, 20);
        addPanoramaBtn = new QToolButton(leftWidget);
        addPanoramaBtn->setObjectName(QStringLiteral("addPanoramaBtn"));
        addPanoramaBtn->setMinimumSize(QSize(150, 30));
        addPanoramaBtn->setMaximumSize(QSize(150, 30));

        verticalLayout->addWidget(addPanoramaBtn, 0, Qt::AlignHCenter);

        line = new QFrame(leftWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setMinimumSize(QSize(0, 1));
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QStringLiteral("background:rgba(17,17,17,1);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        listWidget = new commonListWidget(leftWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setDragEnabled(false);
        listWidget->setDragDropOverwriteMode(false);
        listWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        listWidget->setDefaultDropAction(Qt::CopyAction);
        listWidget->setAlternatingRowColors(false);

        verticalLayout->addWidget(listWidget);


        horizontalLayout->addWidget(leftWidget);

        rightWidget = new QWidget(VRMapWidget);
        rightWidget->setObjectName(QStringLiteral("rightWidget"));
        gridLayout = new QGridLayout(rightWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(rightWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        initPage = new QWidget();
        initPage->setObjectName(QStringLiteral("initPage"));
        gridLayout_2 = new QGridLayout(initPage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 55);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(9);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(initPage);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(72, 17));
        label->setMaximumSize(QSize(72, 17));

        horizontalLayout_2->addWidget(label);

        addMapBtn = new QPushButton(initPage);
        addMapBtn->setObjectName(QStringLiteral("addMapBtn"));
        addMapBtn->setMinimumSize(QSize(28, 28));
        addMapBtn->setMaximumSize(QSize(28, 28));

        horizontalLayout_2->addWidget(addMapBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        stackedWidget->addWidget(initPage);
        mapPage = new MapWgt();
        mapPage->setObjectName(QStringLiteral("mapPage"));
        stackedWidget->addWidget(mapPage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        horizontalLayout->addWidget(rightWidget);


        retranslateUi(VRMapWidget);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(VRMapWidget);
    } // setupUi

    void retranslateUi(QWidget *VRMapWidget)
    {
        VRMapWidget->setWindowTitle(QApplication::translate("VRMapWidget", "VRMapWidget", 0));
        addPanoramaBtn->setText(QApplication::translate("VRMapWidget", "+ \346\267\273\345\212\240\345\205\250\346\231\257", 0));
        label->setText(QApplication::translate("VRMapWidget", "\347\202\271\345\207\273\346\267\273\345\212\240\345\234\260\345\233\276", 0));
        addMapBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VRMapWidget: public Ui_VRMapWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VRMAPWIDGET_H
