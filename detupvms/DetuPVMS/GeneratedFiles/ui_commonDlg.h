/********************************************************************************
** Form generated from reading UI file 'commonDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONDLG_H
#define UI_COMMONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "aboutwidget.h"
#include "dlg_titlewgt.h"
#include "loginwidget.h"
#include "serversettingwgt.h"
#include "setadminwgt.h"
#include "settingwidget.h"
#include "unlockwgt.h"

QT_BEGIN_NAMESPACE

class Ui_commonDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *homeWgt;
    QVBoxLayout *verticalLayout;
    dlg_titleWgt *tittleWgt;
    QWidget *loginWgt;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    loginWidget *loginPage;
    setAdminWgt *setAdminPage;
    unlockWgt *unlockPage;
    aboutWidget *aboutPage;
    settingWidget *settingPage;
    serverSettingWgt *serverSettingsPage;

    void setupUi(QDialog *commonDlg)
    {
        if (commonDlg->objectName().isEmpty())
            commonDlg->setObjectName(QStringLiteral("commonDlg"));
        commonDlg->resize(521, 335);
        commonDlg->setMinimumSize(QSize(521, 335));
        commonDlg->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(commonDlg);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        homeWgt = new QWidget(commonDlg);
        homeWgt->setObjectName(QStringLiteral("homeWgt"));
        homeWgt->setStyleSheet(QLatin1String("#homeWgt{\n"
"box-shadow:0 2px 10px 1px rgba(0,0,0,0.20);\n"
"border-radius:4px;\n"
"}"));
        verticalLayout = new QVBoxLayout(homeWgt);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tittleWgt = new dlg_titleWgt(homeWgt);
        tittleWgt->setObjectName(QStringLiteral("tittleWgt"));
        tittleWgt->setMinimumSize(QSize(0, 32));
        tittleWgt->setMaximumSize(QSize(16777215, 32));
        tittleWgt->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(tittleWgt);

        loginWgt = new QWidget(homeWgt);
        loginWgt->setObjectName(QStringLiteral("loginWgt"));
        loginWgt->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(loginWgt);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(loginWgt);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        loginPage = new loginWidget();
        loginPage->setObjectName(QStringLiteral("loginPage"));
        stackedWidget->addWidget(loginPage);
        setAdminPage = new setAdminWgt();
        setAdminPage->setObjectName(QStringLiteral("setAdminPage"));
        stackedWidget->addWidget(setAdminPage);
        unlockPage = new unlockWgt();
        unlockPage->setObjectName(QStringLiteral("unlockPage"));
        stackedWidget->addWidget(unlockPage);
        aboutPage = new aboutWidget();
        aboutPage->setObjectName(QStringLiteral("aboutPage"));
        stackedWidget->addWidget(aboutPage);
        settingPage = new settingWidget();
        settingPage->setObjectName(QStringLiteral("settingPage"));
        stackedWidget->addWidget(settingPage);
        serverSettingsPage = new serverSettingWgt();
        serverSettingsPage->setObjectName(QStringLiteral("serverSettingsPage"));
        stackedWidget->addWidget(serverSettingsPage);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout->addWidget(loginWgt);


        horizontalLayout->addWidget(homeWgt);


        retranslateUi(commonDlg);

        QMetaObject::connectSlotsByName(commonDlg);
    } // setupUi

    void retranslateUi(QDialog *commonDlg)
    {
        commonDlg->setWindowTitle(QApplication::translate("commonDlg", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class commonDlg: public Ui_commonDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONDLG_H
