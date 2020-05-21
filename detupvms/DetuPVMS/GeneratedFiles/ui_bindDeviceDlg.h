/********************************************************************************
** Form generated from reading UI file 'bindDeviceDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BINDDEVICEDLG_H
#define UI_BINDDEVICEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_bindDeviceDlg
{
public:
    QGridLayout *gridLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QWidget *contentWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *ptzBtn;
    QPushButton *spyBtn;
    QPushButton *hotBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_5;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *title;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QListWidget *listWidget;
    QWidget *control;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *addBtn;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *confirmBtn;
    QPushButton *cancelBtn;
    QPushButton *clearButton;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QDialog *bindDeviceDlg)
    {
        if (bindDeviceDlg->objectName().isEmpty())
            bindDeviceDlg->setObjectName(QStringLiteral("bindDeviceDlg"));
        bindDeviceDlg->resize(518, 354);
        bindDeviceDlg->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#333333;\n"
"}\n"
"QPushButton{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"}\n"
"#titleWidget{\n"
"background:#ffffff;\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#contentWidget{\n"
"background:#eeeeee;\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"#ptzBtn{\n"
"border:1px solid #cccccc;\n"
"border-top-left-radius:14px;\n"
"border-bottom-left-radius:14px;\n"
"border-right:none;\n"
"color:#888888;\n"
"}\n"
"#ptzBtn:checked{\n"
"background:#cccccc;\n"
"color:#222222;\n"
"}\n"
"#spyBtn{\n"
"border:1px solid #cccccc;\n"
"color:#888888;\n"
"}\n"
"#spyBtn:checked{\n"
"background:#cccccc;\n"
"color:#222222;\n"
"}\n"
"#hotBtn{\n"
"border:1px solid #cccccc;\n"
"border-top-right-radius:14px;\n"
"border-bottom-right-radius:14px;\n"
"color:#888888;\n"
"}\n"
"#hotBtn:checked{\n"
"background:#cccccc;\n"
""
                        "color:#222222;\n"
"}\n"
"#title{\n"
"background-color: rgb(255, 255, 255);\n"
"border:1px solid #cccccc;\n"
"border-bottom:none;\n"
"}\n"
"#control{\n"
"background-color: rgb(255, 255, 255);\n"
"border:1px solid #cccccc;\n"
"border-top:none;\n"
"}\n"
"#addBtn{\n"
"background:#ffffff;\n"
"border:none;\n"
"}"));
        gridLayout = new QGridLayout(bindDeviceDlg);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, 0, 0);
        titleWidget = new QWidget(bindDeviceDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);


        gridLayout->addWidget(titleWidget, 0, 0, 1, 1);

        contentWidget = new QWidget(bindDeviceDlg);
        contentWidget->setObjectName(QStringLiteral("contentWidget"));
        verticalLayout = new QVBoxLayout(contentWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 20, 0, 20);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        ptzBtn = new QPushButton(contentWidget);
        ptzBtn->setObjectName(QStringLiteral("ptzBtn"));
        ptzBtn->setMinimumSize(QSize(80, 28));
        ptzBtn->setMaximumSize(QSize(80, 28));
        ptzBtn->setCheckable(true);
        ptzBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(ptzBtn);

        spyBtn = new QPushButton(contentWidget);
        spyBtn->setObjectName(QStringLiteral("spyBtn"));
        spyBtn->setMinimumSize(QSize(80, 28));
        spyBtn->setMaximumSize(QSize(80, 28));
        spyBtn->setCheckable(true);
        spyBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(spyBtn);

        hotBtn = new QPushButton(contentWidget);
        hotBtn->setObjectName(QStringLiteral("hotBtn"));
        hotBtn->setMinimumSize(QSize(80, 28));
        hotBtn->setMaximumSize(QSize(80, 28));
        hotBtn->setCheckable(true);
        hotBtn->setAutoExclusive(true);

        horizontalLayout_2->addWidget(hotBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_2 = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        widget = new QWidget(contentWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(320, 120));
        widget->setMaximumSize(QSize(320, 120));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        title = new QWidget(widget);
        title->setObjectName(QStringLiteral("title"));
        title->setMinimumSize(QSize(0, 30));
        title->setMaximumSize(QSize(16777215, 30));
        title->setStyleSheet(QLatin1String("QLabel{\n"
"color:#666666;\n"
"}\n"
""));
        horizontalLayout_4 = new QHBoxLayout(title);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label = new QLabel(title);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_4->addWidget(label, 0, Qt::AlignHCenter);

        label_2 = new QLabel(title);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2, 0, Qt::AlignHCenter);

        label_3 = new QLabel(title);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3, 0, Qt::AlignHCenter);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);

        verticalLayout_2->addWidget(title);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QLatin1String("\n"
"#listWidget{\n"
"border:1px solid #cccccc;\n"
"}\n"
"\n"
""));

        verticalLayout_2->addWidget(listWidget);

        control = new QWidget(widget);
        control->setObjectName(QStringLiteral("control"));
        control->setMinimumSize(QSize(0, 30));
        control->setMaximumSize(QSize(16777215, 30));
        control->setStyleSheet(QLatin1String("QPushButton{\n"
"color:#666666;\n"
"}\n"
"QPushButton:hover{\n"
"background:#eeeeee;\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(control);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(1, 0, 1, 0);
        addBtn = new QPushButton(control);
        addBtn->setObjectName(QStringLiteral("addBtn"));
        addBtn->setMinimumSize(QSize(0, 29));
        addBtn->setMaximumSize(QSize(16777215, 29));

        horizontalLayout_5->addWidget(addBtn);


        verticalLayout_2->addWidget(control);


        horizontalLayout_6->addWidget(widget);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        label_4 = new QLabel(contentWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(12);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        confirmBtn = new QPushButton(contentWidget);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));
        confirmBtn->setStyleSheet(QLatin1String("#confirmBtn{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(confirmBtn);

        cancelBtn = new QPushButton(contentWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));
        cancelBtn->setStyleSheet(QLatin1String("#cancelBtn{\n"
"background:#ffffff;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#cancelBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(cancelBtn);

        clearButton = new QPushButton(contentWidget);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setMinimumSize(QSize(0, 26));
        clearButton->setMaximumSize(QSize(200, 16777215));
        clearButton->setLayoutDirection(Qt::LeftToRight);
        clearButton->setStyleSheet(QLatin1String("\n"
"#clearButton{\n"
"background:#ffd500;\n"
"border-radius:2px;\n"
"color:#333333;\n"
"}\n"
"#confirmBtn:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout_3->addWidget(clearButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_3);


        gridLayout->addWidget(contentWidget, 1, 0, 1, 1);


        retranslateUi(bindDeviceDlg);

        QMetaObject::connectSlotsByName(bindDeviceDlg);
    } // setupUi

    void retranslateUi(QDialog *bindDeviceDlg)
    {
        bindDeviceDlg->setWindowTitle(QApplication::translate("bindDeviceDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("bindDeviceDlg", "\347\273\221\345\256\232\350\256\276\345\244\207", 0));
        ptzBtn->setText(QApplication::translate("bindDeviceDlg", "\347\220\203\346\234\272", 0));
        spyBtn->setText(QApplication::translate("bindDeviceDlg", "\346\236\252\346\234\272", 0));
        hotBtn->setText(QApplication::translate("bindDeviceDlg", "\347\203\255\347\202\271", 0));
        label->setText(QApplication::translate("bindDeviceDlg", "IP", 0));
        label_2->setText(QApplication::translate("bindDeviceDlg", "\347\253\257\345\217\243", 0));
        label_3->setText(QApplication::translate("bindDeviceDlg", "\346\223\215\344\275\234", 0));
        addBtn->setText(QApplication::translate("bindDeviceDlg", "+ \346\267\273\345\212\240\347\220\203\346\234\272", 0));
        label_4->setText(QApplication::translate("bindDeviceDlg", "\347\202\271\345\207\273\347\241\256\345\256\232\346\267\273\345\212\240\347\203\255\347\202\271\345\233\276\347\211\207", 0));
        confirmBtn->setText(QApplication::translate("bindDeviceDlg", "\347\241\256\350\256\244", 0));
        cancelBtn->setText(QApplication::translate("bindDeviceDlg", "\345\217\226\346\266\210", 0));
        clearButton->setText(QApplication::translate("bindDeviceDlg", "\347\202\271\345\207\273\346\270\205\351\231\244\346\211\200\346\234\211\347\203\255\347\202\271", 0));
    } // retranslateUi

};

namespace Ui {
    class bindDeviceDlg: public Ui_bindDeviceDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BINDDEVICEDLG_H
