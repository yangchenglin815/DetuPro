/********************************************************************************
** Form generated from reading UI file 'RFIDScreen.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RFIDSCREEN_H
#define UI_RFIDSCREEN_H

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

class Ui_RFIDScreen
{
public:
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_5;
    QLabel *title_label;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton1;
    QLabel *text_label;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton2;
    QLabel *text_label_2;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_7;
    QPushButton *pushButton3;
    QLabel *text_label_3;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_9;
    QPushButton *pushButton4;
    QLabel *text_label_4;

    void setupUi(QWidget *RFIDScreen)
    {
        if (RFIDScreen->objectName().isEmpty())
            RFIDScreen->setObjectName(QStringLiteral("RFIDScreen"));
        RFIDScreen->resize(320, 334);
        RFIDScreen->setMinimumSize(QSize(320, 0));
        RFIDScreen->setMaximumSize(QSize(320, 16777215));
        RFIDScreen->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background:#1f2020;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:18px;\n"
"color:#eeeeee;\n"
"}\n"
"QPushButton{\n"
"background:#1f2020;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:18px;\n"
"color:#ffffff;\n"
"border-radius:0px\n"
"}\n"
""));
        gridLayout_10 = new QGridLayout(RFIDScreen);
        gridLayout_10->setSpacing(0);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(0);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        title_label = new QLabel(RFIDScreen);
        title_label->setObjectName(QStringLiteral("title_label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(title_label->sizePolicy().hasHeightForWidth());
        title_label->setSizePolicy(sizePolicy);
        title_label->setMinimumSize(QSize(0, 30));
        title_label->setMaximumSize(QSize(16777215, 30));
        title_label->setStyleSheet(QStringLiteral(""));
        title_label->setAlignment(Qt::AlignCenter);

        gridLayout_5->addWidget(title_label, 0, 0, 1, 1);


        gridLayout_10->addLayout(gridLayout_5, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton1 = new QPushButton(RFIDScreen);
        pushButton1->setObjectName(QStringLiteral("pushButton1"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton1->sizePolicy().hasHeightForWidth());
        pushButton1->setSizePolicy(sizePolicy1);
        pushButton1->setMinimumSize(QSize(60, 0));
        pushButton1->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(pushButton1, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        text_label = new QLabel(RFIDScreen);
        text_label->setObjectName(QStringLiteral("text_label"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text_label->sizePolicy().hasHeightForWidth());
        text_label->setSizePolicy(sizePolicy2);
        text_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_2->addWidget(text_label, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_2, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton2 = new QPushButton(RFIDScreen);
        pushButton2->setObjectName(QStringLiteral("pushButton2"));
        sizePolicy1.setHeightForWidth(pushButton2->sizePolicy().hasHeightForWidth());
        pushButton2->setSizePolicy(sizePolicy1);
        pushButton2->setMinimumSize(QSize(60, 0));
        pushButton2->setMaximumSize(QSize(60, 16777215));

        gridLayout_3->addWidget(pushButton2, 0, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 0, 1, 1);

        text_label_2 = new QLabel(RFIDScreen);
        text_label_2->setObjectName(QStringLiteral("text_label_2"));
        sizePolicy2.setHeightForWidth(text_label_2->sizePolicy().hasHeightForWidth());
        text_label_2->setSizePolicy(sizePolicy2);
        text_label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_4->addWidget(text_label_2, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_4, 2, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(0);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        pushButton3 = new QPushButton(RFIDScreen);
        pushButton3->setObjectName(QStringLiteral("pushButton3"));
        sizePolicy1.setHeightForWidth(pushButton3->sizePolicy().hasHeightForWidth());
        pushButton3->setSizePolicy(sizePolicy1);
        pushButton3->setMinimumSize(QSize(60, 0));
        pushButton3->setMaximumSize(QSize(60, 16777215));

        gridLayout_7->addWidget(pushButton3, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_7, 0, 0, 1, 1);

        text_label_3 = new QLabel(RFIDScreen);
        text_label_3->setObjectName(QStringLiteral("text_label_3"));
        sizePolicy2.setHeightForWidth(text_label_3->sizePolicy().hasHeightForWidth());
        text_label_3->setSizePolicy(sizePolicy2);
        text_label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_6->addWidget(text_label_3, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_6, 3, 0, 1, 1);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(0);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(0);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        pushButton4 = new QPushButton(RFIDScreen);
        pushButton4->setObjectName(QStringLiteral("pushButton4"));
        sizePolicy1.setHeightForWidth(pushButton4->sizePolicy().hasHeightForWidth());
        pushButton4->setSizePolicy(sizePolicy1);
        pushButton4->setMinimumSize(QSize(60, 0));
        pushButton4->setMaximumSize(QSize(60, 16777215));

        gridLayout_9->addWidget(pushButton4, 0, 0, 1, 1);


        gridLayout_8->addLayout(gridLayout_9, 0, 0, 1, 1);

        text_label_4 = new QLabel(RFIDScreen);
        text_label_4->setObjectName(QStringLiteral("text_label_4"));
        sizePolicy2.setHeightForWidth(text_label_4->sizePolicy().hasHeightForWidth());
        text_label_4->setSizePolicy(sizePolicy2);
        text_label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout_8->addWidget(text_label_4, 0, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 4, 0, 1, 1);


        retranslateUi(RFIDScreen);

        QMetaObject::connectSlotsByName(RFIDScreen);
    } // setupUi

    void retranslateUi(QWidget *RFIDScreen)
    {
        RFIDScreen->setWindowTitle(QApplication::translate("RFIDScreen", "RFIDScreen", 0));
        title_label->setText(QApplication::translate("RFIDScreen", "\351\200\232\347\237\245\345\206\205\345\256\271", 0));
        pushButton1->setText(QApplication::translate("RFIDScreen", "\351\227\250\347\246\201", 0));
        text_label->setText(QString());
        pushButton2->setText(QApplication::translate("RFIDScreen", "\345\215\261\351\231\251\345\214\272", 0));
        text_label_2->setText(QString());
        pushButton3->setText(QApplication::translate("RFIDScreen", "\346\235\203\351\231\220\345\214\272", 0));
        text_label_3->setText(QString());
        pushButton4->setText(QApplication::translate("RFIDScreen", "\350\255\246\347\244\272\347\211\214", 0));
        text_label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RFIDScreen: public Ui_RFIDScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RFIDSCREEN_H
