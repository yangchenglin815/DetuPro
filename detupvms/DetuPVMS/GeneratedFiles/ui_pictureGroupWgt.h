/********************************************************************************
** Form generated from reading UI file 'pictureGroupWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTUREGROUPWGT_H
#define UI_PICTUREGROUPWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pictureGroupWgt
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *closeBtn;
    QListWidget *listWidget;

    void setupUi(QWidget *pictureGroupWgt)
    {
        if (pictureGroupWgt->objectName().isEmpty())
            pictureGroupWgt->setObjectName(QStringLiteral("pictureGroupWgt"));
        pictureGroupWgt->resize(366, 226);
        pictureGroupWgt->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffffff;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(pictureGroupWgt);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(pictureGroupWgt);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 25));
        titleWidget->setMaximumSize(QSize(16777215, 25));
        titleWidget->setStyleSheet(QLatin1String("#titleWidget{\n"
"background:#2A2B2B;\n"
"border-bottom:1px solid #000000;\n"
"}"));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 9, 0);
        label = new QLabel(titleWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        closeBtn = new QPushButton(titleWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(8, 7));
        closeBtn->setMaximumSize(QSize(8, 7));
        closeBtn->setStyleSheet(QLatin1String("#closeBtn{\n"
"border-image:url(:/image/image/popupx.png);\n"
"}\n"
"#closeBtn:pressed{\n"
" margin:1px;\n"
"}"));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addWidget(titleWidget);

        listWidget = new QListWidget(pictureGroupWgt);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QString::fromUtf8("#listWidget{\n"
"background:#2A2B2B;\n"
"border:none;\n"
"}\n"
" #scrollArea{\n"
"border:none;\n"
"}\n"
"QScrollBar:horizontal {\n"
"      height:12px;\n"
"      background: #1f2020;\n"
"      padding-left:14px;\n"
"      padding-right: 14px;\n"
"      margin: 0px 0px 3px 0px;\n"
"}\n"
"QScrollBar:vertical{\n"
"   width:12px;\n"
"   background: #1f2020;\n"
"     margin-right:3px;\n"
"      margin-bottom:3px;\n"
"min-height:40;\n"
"}\n"
"QScrollBar::handle:vertical{\n"
"   background:#4e5050;\n"
"    border-radius:4px;\n"
"min-height:40;\n"
"}\n"
"QScrollBar::handle:vertical:hover{\n"
"    background:#888888; \n"
"    border-radius:4px;\n"
"min-height:40;\n"
"}\n"
"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical  \n"
"{\n"
"    background:#1f2020;\n"
"}\n"
"QScrollBar::handle:horizontal{\n"
"    background:#4e5050;\n"
"    border-radius:4px;\n"
"    min-width:20;\n"
"}\n"
"QScrollBar::handle:horizontal:hover\n"
"{\n"
"    background:#888888; \n"
"    border-radius:4px;\n"
"        min-width:20;\n"
""
                        "}\n"
"QScrollBar::add-line:horizontal {\n"
"      /*border: none;\n"
"      background: #1f2020;*/\n"
"border-image:url(:/res/right.png);\n"
"}\n"
"QScrollBar::add-line:horizontal:hover {\n"
"border-image:url(:/res/rightb.png);\n"
"}\n"
"\n"
"QScrollBar::add-line:horizontal:pressed {\n"
"margin:1px;\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal {\n"
"     /* border: none;\n"
"      background: #1f2020;*/\n"
"border-image:url(:/res/left.png);\n"
"}  \n"
"QScrollBar::sub-line:horizontal:hover {\n"
"border-image:url(:/res/leftb.png);\n"
"}\n"
"\n"
"QScrollBar::sub-line:horizontal:pressed {\n"
"margin:1px;\n"
"}\n"
"\n"
"QScrollBar::add-page:horizontal,QScrollBar::sub-page:horizontal  \n"
"{\n"
"    background:#1f2020;\n"
"    border-radius:4px;\n"
"}\n"
"\n"
" QListView {\n"
"      color:rgba(255,255,255,1);\n"
"font-size:11px;\n"
"line-height:11px;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"outline:0px;\n"
"  }\n"
"  QListView::item:selected {\n"
"      border: 1px solid #FFD500;\n"
""
                        "  }\n"
"\n"
"\n"
"  QListView::item:hover {\n"
"border:1px solid rgb(0, 146, 254);\n"
"  }\n"
""));

        verticalLayout->addWidget(listWidget);


        retranslateUi(pictureGroupWgt);

        QMetaObject::connectSlotsByName(pictureGroupWgt);
    } // setupUi

    void retranslateUi(QWidget *pictureGroupWgt)
    {
        pictureGroupWgt->setWindowTitle(QApplication::translate("pictureGroupWgt", "Form", 0));
        label->setText(QApplication::translate("pictureGroupWgt", "\345\205\250\346\231\257\345\234\272\346\231\257\347\273\204\345\233\276", 0));
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class pictureGroupWgt: public Ui_pictureGroupWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTUREGROUPWGT_H
