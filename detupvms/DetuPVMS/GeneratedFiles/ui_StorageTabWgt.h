/********************************************************************************
** Form generated from reading UI file 'StorageTabWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STORAGETABWGT_H
#define UI_STORAGETABWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StorageTabWgt
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *StorageTabWgt)
    {
        if (StorageTabWgt->objectName().isEmpty())
            StorageTabWgt->setObjectName(QStringLiteral("StorageTabWgt"));
        StorageTabWgt->resize(190, 41);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StorageTabWgt->sizePolicy().hasHeightForWidth());
        StorageTabWgt->setSizePolicy(sizePolicy);
        StorageTabWgt->setMinimumSize(QSize(0, 38));
        StorageTabWgt->setMaximumSize(QSize(16777215, 41));
        gridLayout = new QGridLayout(StorageTabWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(StorageTabWgt);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("#widget{\n"
"background:#1f2020;\n"
"border:1px solid #000000;\n"
"}"));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(23, 23));
        pushButton->setMaximumSize(QSize(23, 23));
        pushButton->setStyleSheet(QStringLiteral("background:#323232;"));

        gridLayout_2->addWidget(pushButton, 0, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(24, 14));
        label->setMaximumSize(QSize(16777215, 14));
        label->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#eeeeee;\n"
"text-align:left;"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 0, 1, 1, 1);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(StorageTabWgt);

        QMetaObject::connectSlotsByName(StorageTabWgt);
    } // setupUi

    void retranslateUi(QWidget *StorageTabWgt)
    {
        StorageTabWgt->setWindowTitle(QApplication::translate("StorageTabWgt", "StorageTabWgt", 0));
        pushButton->setText(QString());
        label->setText(QApplication::translate("StorageTabWgt", "\345\255\230\345\202\250\350\256\276\347\275\256", 0));
    } // retranslateUi

};

namespace Ui {
    class StorageTabWgt: public Ui_StorageTabWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STORAGETABWGT_H
