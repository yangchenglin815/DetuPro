/********************************************************************************
** Form generated from reading UI file 'addItemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDITEMWIDGET_H
#define UI_ADDITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addItemWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *ipLabel;
    QLabel *portLabel;
    QPushButton *settingsBtn;
    QPushButton *unbindBtn;

    void setupUi(QWidget *addItemWidget)
    {
        if (addItemWidget->objectName().isEmpty())
            addItemWidget->setObjectName(QStringLiteral("addItemWidget"));
        addItemWidget->resize(254, 30);
        addItemWidget->setMinimumSize(QSize(0, 30));
        addItemWidget->setMaximumSize(QSize(16777215, 30));
        addItemWidget->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#666666;\n"
"border:none;\n"
"}\n"
"#settingsBtn{\n"
"border-image:url(:/image/image/setup2.png);\n"
"}\n"
"#settingsBtn:hover{\n"
"border-image:url(:/image/image/setup2b.png);\n"
"}\n"
"#settingsBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#unbindBtn{\n"
"border-image:url(:/image/image/unbind.png);\n"
"}\n"
"#unbindBtn:hover{\n"
"border-image:url(:/image/image/unbind2.png);\n"
"}\n"
"#unbindBtn:pressed{\n"
"margin:1px;\n"
"}"));
        horizontalLayout = new QHBoxLayout(addItemWidget);
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, 30, 0);
        ipLabel = new QLabel(addItemWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));

        horizontalLayout->addWidget(ipLabel, 0, Qt::AlignHCenter);

        portLabel = new QLabel(addItemWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setMinimumSize(QSize(40, 0));

        horizontalLayout->addWidget(portLabel, 0, Qt::AlignHCenter);

        settingsBtn = new QPushButton(addItemWidget);
        settingsBtn->setObjectName(QStringLiteral("settingsBtn"));
        settingsBtn->setMinimumSize(QSize(16, 16));
        settingsBtn->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(settingsBtn);

        unbindBtn = new QPushButton(addItemWidget);
        unbindBtn->setObjectName(QStringLiteral("unbindBtn"));
        unbindBtn->setMinimumSize(QSize(16, 16));
        unbindBtn->setMaximumSize(QSize(16, 16));

        horizontalLayout->addWidget(unbindBtn);


        retranslateUi(addItemWidget);

        QMetaObject::connectSlotsByName(addItemWidget);
    } // setupUi

    void retranslateUi(QWidget *addItemWidget)
    {
        addItemWidget->setWindowTitle(QApplication::translate("addItemWidget", "Form", 0));
        ipLabel->setText(QApplication::translate("addItemWidget", "192.168.100.1", 0));
        portLabel->setText(QApplication::translate("addItemWidget", "8088", 0));
#ifndef QT_NO_TOOLTIP
        settingsBtn->setToolTip(QApplication::translate("addItemWidget", "<html><head/><body><p>\350\256\276\347\275\256</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        settingsBtn->setText(QString());
#ifndef QT_NO_TOOLTIP
        unbindBtn->setToolTip(QApplication::translate("addItemWidget", "<html><head/><body><p>\350\247\243\347\273\221</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        unbindBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class addItemWidget: public Ui_addItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDITEMWIDGET_H
