/********************************************************************************
** Form generated from reading UI file 'commonTipDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMONTIPDLG_H
#define UI_COMMONTIPDLG_H

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
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_commonTipDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *tipLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *commonTipDlg)
    {
        if (commonTipDlg->objectName().isEmpty())
            commonTipDlg->setObjectName(QStringLiteral("commonTipDlg"));
        commonTipDlg->resize(344, 193);
        commonTipDlg->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color: #eeeeee;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#868989;\n"
"line-height:12px;\n"
"text-align:right;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"letter-spacing:0;\n"
"line-height:12px;\n"
"text-align:center;\n"
"}"));
        verticalLayout = new QVBoxLayout(commonTipDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(commonTipDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        titleWidget->setStyleSheet(QLatin1String("#titleWidget{\n"
"border:1px solid #eeeeee;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"background:#ffffff;\n"
"}"));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        titleLabel->setStyleSheet(QStringLiteral("background:#ffffff;"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);


        verticalLayout->addWidget(titleWidget);

        contentWidget = new QWidget(commonTipDlg);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        contentWidget->setStyleSheet(QLatin1String("#contentWidget{\n"
"border:1px solid #eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(contentWidget);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(12, 40, 12, 40);
        tipLabel = new QLabel(contentWidget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tipLabel->sizePolicy().hasHeightForWidth());
        tipLabel->setSizePolicy(sizePolicy);
        tipLabel->setScaledContents(false);
        tipLabel->setAlignment(Qt::AlignCenter);
        tipLabel->setWordWrap(true);

        verticalLayout_2->addWidget(tipLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelBtn = new QPushButton(contentWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(cancelBtn);

        confirmBtn = new QPushButton(contentWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_2->addWidget(confirmBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(contentWidget);


        retranslateUi(commonTipDlg);

        QMetaObject::connectSlotsByName(commonTipDlg);
    } // setupUi

    void retranslateUi(QDialog *commonTipDlg)
    {
        commonTipDlg->setWindowTitle(QApplication::translate("commonTipDlg", "Dialog", 0));
        titleLabel->setText(QString());
        tipLabel->setText(QString());
        cancelBtn->setText(QApplication::translate("commonTipDlg", "\345\217\226\346\266\210", 0));
        confirmBtn->setText(QApplication::translate("commonTipDlg", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class commonTipDlg: public Ui_commonTipDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMONTIPDLG_H
