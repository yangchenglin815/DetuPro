/********************************************************************************
** Form generated from reading UI file 'MapPointSetingWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPPOINTSETINGWGT_H
#define UI_MAPPOINTSETINGWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapPointSetingWgt
{
public:
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *GviewBtn_;
    QPushButton *ConnBtn_;
    QPushButton *DeleteBtn_;

    void setupUi(QWidget *MapPointSetingWgt)
    {
        if (MapPointSetingWgt->objectName().isEmpty())
            MapPointSetingWgt->setObjectName(QStringLiteral("MapPointSetingWgt"));
        MapPointSetingWgt->resize(94, 78);
        MapPointSetingWgt->setStyleSheet(QString::fromUtf8("#widget{\n"
"background:#ffffff;\n"
"border-radius:4px;\n"
"}\n"
"QPushButton{\n"
"font-size:12px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"background:#ffffff;\n"
"border:none;\n"
"padding-left:10px;\n"
"}\n"
"QPushButton:hover{\n"
"background:rgba(232,232,232,1);\n"
"}"));
        gridLayout = new QGridLayout(MapPointSetingWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(MapPointSetingWgt);
        widget->setObjectName(QStringLiteral("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 4, 0, 4);
        GviewBtn_ = new QPushButton(widget);
        GviewBtn_->setObjectName(QStringLiteral("GviewBtn_"));
        GviewBtn_->setMinimumSize(QSize(94, 22));
        GviewBtn_->setMaximumSize(QSize(94, 22));
        GviewBtn_->setMouseTracking(false);
        GviewBtn_->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#505252;\n"
"text-align:left;"));

        verticalLayout->addWidget(GviewBtn_);

        ConnBtn_ = new QPushButton(widget);
        ConnBtn_->setObjectName(QStringLiteral("ConnBtn_"));
        ConnBtn_->setMinimumSize(QSize(94, 22));
        ConnBtn_->setMaximumSize(QSize(94, 22));
        ConnBtn_->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#505252;\n"
"text-align:left;"));

        verticalLayout->addWidget(ConnBtn_);

        DeleteBtn_ = new QPushButton(widget);
        DeleteBtn_->setObjectName(QStringLiteral("DeleteBtn_"));
        DeleteBtn_->setMinimumSize(QSize(94, 22));
        DeleteBtn_->setMaximumSize(QSize(94, 22));
        DeleteBtn_->setStyleSheet(QString::fromUtf8("font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#505252;\n"
"text-align:left;"));

        verticalLayout->addWidget(DeleteBtn_);


        gridLayout->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(MapPointSetingWgt);

        QMetaObject::connectSlotsByName(MapPointSetingWgt);
    } // setupUi

    void retranslateUi(QWidget *MapPointSetingWgt)
    {
        MapPointSetingWgt->setWindowTitle(QApplication::translate("MapPointSetingWgt", "MapPointSetingWgt", 0));
        GviewBtn_->setText(QApplication::translate("MapPointSetingWgt", "\350\260\203\346\225\264\350\247\206\350\247\222", 0));
        ConnBtn_->setText(QApplication::translate("MapPointSetingWgt", "\350\267\257\345\276\204\350\277\236\346\216\245\350\207\263..", 0));
        DeleteBtn_->setText(QApplication::translate("MapPointSetingWgt", "\347\247\273\351\231\244\347\233\270\346\234\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MapPointSetingWgt: public Ui_MapPointSetingWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPOINTSETINGWGT_H
