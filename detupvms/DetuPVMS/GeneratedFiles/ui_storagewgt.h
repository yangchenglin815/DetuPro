/********************************************************************************
** Form generated from reading UI file 'storagewgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STORAGEWGT_H
#define UI_STORAGEWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "storagelistview.h"
#include "storagetitlewgt.h"

QT_BEGIN_NAMESPACE

class Ui_storageWgt
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget *controlWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *refreshBtn;
    QToolButton *clearBtn;
    QSpacerItem *horizontalSpacer;
    storageTitleWgt *titleWidget;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    storageListView *listView;

    void setupUi(QWidget *storageWgt)
    {
        if (storageWgt->objectName().isEmpty())
            storageWgt->setObjectName(QStringLiteral("storageWgt"));
        storageWgt->resize(1200, 657);
        horizontalLayout = new QHBoxLayout(storageWgt);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(storageWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#1f2020;\n"
"box-shadow:0 10px 20px 3px rgba(0,0,0,0.50);\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(210, 36, 210, 20);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        controlWidget = new QWidget(widget);
        controlWidget->setObjectName(QStringLiteral("controlWidget"));
        controlWidget->setMinimumSize(QSize(0, 44));
        controlWidget->setMaximumSize(QSize(16777215, 44));
        horizontalLayout_2 = new QHBoxLayout(controlWidget);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        refreshBtn = new QPushButton(controlWidget);
        refreshBtn->setObjectName(QStringLiteral("refreshBtn"));
        refreshBtn->setMinimumSize(QSize(84, 28));
        refreshBtn->setMaximumSize(QSize(84, 28));
        refreshBtn->setStyleSheet(QString::fromUtf8("#refreshBtn{\n"
"border:1px solid #868989;\n"
"border-radius:14px;\n"
"color:#868989;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"background-image:url(:/image/image/refresh.png);\n"
"background-size:26px 14px;\n"
"background-repeat:no-repeat;\n"
"background-position:left;\n"
"}\n"
"#refreshBtn:pressed{\n"
"padding-left:3px;\n"
"padding-top:3px;\n"
"}\n"
"#refreshBtn:hover{\n"
"border:1px solid #eeeeee;\n"
"color:#eeeeee;\n"
"background-image:url(:/image/image/refreshb.png);\n"
"}"));
        refreshBtn->setIconSize(QSize(14, 14));

        horizontalLayout_2->addWidget(refreshBtn);

        clearBtn = new QToolButton(controlWidget);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));
        clearBtn->setMinimumSize(QSize(84, 28));
        clearBtn->setMaximumSize(QSize(84, 28));
        clearBtn->setStyleSheet(QString::fromUtf8("#clearBtn{\n"
"border:1px solid #868989;\n"
"border-radius:14px;\n"
"color:#868989;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"background-image:url(:/image/image/format.png);\n"
"background-size:26px 14px;\n"
"background-repeat:no-repeat;\n"
"background-position:left;\n"
"}\n"
"#clearBtn:pressed{\n"
"padding-left:3px;\n"
"padding-top:3px;\n"
"}\n"
"#clearBtn:hover{\n"
"border:1px solid #eeeeee;\n"
"color:#eeeeee;\n"
"background-image:url(:/image/image/formatb.png);\n"
"}"));
        clearBtn->setIconSize(QSize(14, 14));
        clearBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        horizontalLayout_2->addWidget(clearBtn);

        horizontalSpacer = new QSpacerItem(579, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(controlWidget);

        titleWidget = new storageTitleWgt(widget);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 44));
        titleWidget->setMaximumSize(QSize(16777215, 44));

        verticalLayout->addWidget(titleWidget);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        listView = new storageListView(widget_4);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setStyleSheet(QLatin1String("background:#1f2020;\n"
"border:none;"));

        horizontalLayout_3->addWidget(listView);


        verticalLayout->addWidget(widget_4);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget);


        retranslateUi(storageWgt);

        QMetaObject::connectSlotsByName(storageWgt);
    } // setupUi

    void retranslateUi(QWidget *storageWgt)
    {
        storageWgt->setWindowTitle(QApplication::translate("storageWgt", "Form", 0));
        refreshBtn->setText(QApplication::translate("storageWgt", "     \345\210\267\346\226\260", 0));
        clearBtn->setText(QApplication::translate("storageWgt", "     \346\240\274\345\274\217\345\214\226", 0));
    } // retranslateUi

};

namespace Ui {
    class storageWgt: public Ui_storageWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STORAGEWGT_H
