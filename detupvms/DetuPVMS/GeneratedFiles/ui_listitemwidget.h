/********************************************************************************
** Form generated from reading UI file 'listitemwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTITEMWIDGET_H
#define UI_LISTITEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ListItemWidget
{
public:
    QGridLayout *gridLayout;
    QPushButton *statusbutton_;
    QCheckBox *checkBox;
    QLabel *devicelabel_;
    QLabel *statuslabel_;

    void setupUi(QWidget *ListItemWidget)
    {
        if (ListItemWidget->objectName().isEmpty())
            ListItemWidget->setObjectName(QStringLiteral("ListItemWidget"));
        ListItemWidget->resize(169, 30);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ListItemWidget->sizePolicy().hasHeightForWidth());
        ListItemWidget->setSizePolicy(sizePolicy);
        ListItemWidget->setMinimumSize(QSize(0, 0));
        ListItemWidget->setMaximumSize(QSize(1666666, 16777215));
        ListItemWidget->setStyleSheet(QLatin1String("QLabel{\n"
"	color:#dddddd;\n"
"}"));
        gridLayout = new QGridLayout(ListItemWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        statusbutton_ = new QPushButton(ListItemWidget);
        statusbutton_->setObjectName(QStringLiteral("statusbutton_"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusbutton_->sizePolicy().hasHeightForWidth());
        statusbutton_->setSizePolicy(sizePolicy1);
        statusbutton_->setMinimumSize(QSize(0, 0));
        statusbutton_->setMaximumSize(QSize(30, 30));

        gridLayout->addWidget(statusbutton_, 0, 0, 1, 1);

        checkBox = new QCheckBox(ListItemWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(checkBox, 0, 1, 1, 1);

        devicelabel_ = new QLabel(ListItemWidget);
        devicelabel_->setObjectName(QStringLiteral("devicelabel_"));
        sizePolicy1.setHeightForWidth(devicelabel_->sizePolicy().hasHeightForWidth());
        devicelabel_->setSizePolicy(sizePolicy1);
        devicelabel_->setMinimumSize(QSize(0, 0));
        devicelabel_->setMaximumSize(QSize(66666, 66666));

        gridLayout->addWidget(devicelabel_, 0, 2, 1, 1);

        statuslabel_ = new QLabel(ListItemWidget);
        statuslabel_->setObjectName(QStringLiteral("statuslabel_"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(statuslabel_->sizePolicy().hasHeightForWidth());
        statuslabel_->setSizePolicy(sizePolicy3);
        statuslabel_->setMinimumSize(QSize(50, 3));
        statuslabel_->setMaximumSize(QSize(50, 66666));

        gridLayout->addWidget(statuslabel_, 0, 3, 1, 1);


        retranslateUi(ListItemWidget);

        QMetaObject::connectSlotsByName(ListItemWidget);
    } // setupUi

    void retranslateUi(QWidget *ListItemWidget)
    {
        ListItemWidget->setWindowTitle(QApplication::translate("ListItemWidget", "ListItemWidget", 0));
        statusbutton_->setText(QString());
        checkBox->setText(QString());
        devicelabel_->setText(QApplication::translate("ListItemWidget", "\350\256\276\345\244\207\345\220\215\347\247\260", 0));
        statuslabel_->setText(QApplication::translate("ListItemWidget", "\347\233\270\346\234\272\347\212\266\346\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class ListItemWidget: public Ui_ListItemWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTITEMWIDGET_H
