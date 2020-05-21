/********************************************************************************
** Form generated from reading UI file 'commonAddDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONADDDLG_H
#define UI_COMMONADDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commonAddDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *tab1;
    QPushButton *tab2;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget_2;
    QWidget *deviceListPage;
    QWidget *sceneListPage;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *commonAddDlg)
    {
        if (commonAddDlg->objectName().isEmpty())
            commonAddDlg->setObjectName(QStringLiteral("commonAddDlg"));
        commonAddDlg->resize(520, 375);
        commonAddDlg->setStyleSheet(QString::fromUtf8("QLabel,\n"
"QPushButton{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#widget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"#titleLabel{\n"
"color:rgba(50,52,52,1);\n"
"}\n"
"#tab1{\n"
"border:1px solid #cccccc;\n"
"border-top-left-radius:14px;\n"
"border-bottom-left-radius:14px;\n"
"border-right:none;\n"
"background:transparent;\n"
"color:#888888;\n"
"}\n"
"#tab1:checked{\n"
"background:#cccccc;\n"
"color:#222222;\n"
"}\n"
"#tab2{\n"
"border:1px solid #cccccc;\n"
"border-top-right-radius:14px;\n"
"border-bottom-right-radius:14px;\n"
"background:transparent;\n"
"color:#888888;\n"
"}\n"
"#tab2:checked{\n"
"background:#cccccc;\n"
"color:#222222;\n"
"}\n"
"#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""
                        "#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#listView{\n"
"border:1px solid #cccccc;\n"
"}\n"
"#selectTitleWidget{\n"
"border:1px solid #cccccc;\n"
"background:#ffffff;\n"
"}"));
        verticalLayout = new QVBoxLayout(commonAddDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(commonAddDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        widget = new QWidget(commonAddDlg);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(100, 20, 100, 40);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        tab1 = new QPushButton(widget);
        tab1->setObjectName(QStringLiteral("tab1"));
        tab1->setMinimumSize(QSize(80, 28));
        tab1->setMaximumSize(QSize(80, 28));
        tab1->setCheckable(true);
        tab1->setAutoExclusive(true);

        horizontalLayout_2->addWidget(tab1);

        tab2 = new QPushButton(widget);
        tab2->setObjectName(QStringLiteral("tab2"));
        tab2->setMinimumSize(QSize(80, 28));
        tab2->setMaximumSize(QSize(80, 28));
        tab2->setCheckable(true);
        tab2->setChecked(false);
        tab2->setAutoExclusive(true);

        horizontalLayout_2->addWidget(tab2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget_2 = new QStackedWidget(widget);
        stackedWidget_2->setObjectName(QStringLiteral("stackedWidget_2"));
        stackedWidget_2->setMinimumSize(QSize(320, 183));
        stackedWidget_2->setMaximumSize(QSize(320, 183));
        deviceListPage = new QWidget();
        deviceListPage->setObjectName(QStringLiteral("deviceListPage"));
        stackedWidget_2->addWidget(deviceListPage);
        sceneListPage = new QWidget();
        sceneListPage->setObjectName(QStringLiteral("sceneListPage"));
        stackedWidget_2->addWidget(sceneListPage);

        verticalLayout_2->addWidget(stackedWidget_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        confirmBtn = new QPushButton(widget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_3->addWidget(confirmBtn);

        cancelBtn = new QPushButton(widget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(widget);


        retranslateUi(commonAddDlg);

        QMetaObject::connectSlotsByName(commonAddDlg);
    } // setupUi

    void retranslateUi(QDialog *commonAddDlg)
    {
        commonAddDlg->setWindowTitle(QApplication::translate("commonAddDlg", "Dialog", 0));
        titleLabel->setText(QString());
        tab1->setText(QString());
        tab2->setText(QString());
        confirmBtn->setText(QApplication::translate("commonAddDlg", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("commonAddDlg", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class commonAddDlg: public Ui_commonAddDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONADDDLG_H
