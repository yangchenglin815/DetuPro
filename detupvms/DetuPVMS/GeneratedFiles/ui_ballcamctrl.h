/********************************************************************************
** Form generated from reading UI file 'ballcamctrl.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALLCAMCTRL_H
#define UI_BALLCAMCTRL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ballCamCtrl
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *savePresetBtn_;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_9;
    QWidget *scaleWgt_;
    QGridLayout *gridLayout_8;
    QPushButton *bigger_;
    QPushButton *smaller_;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_7;
    QWidget *moveWgt_;
    QPushButton *up_;
    QPushButton *left_;
    QPushButton *right_;
    QPushButton *down_;
    QSpacerItem *horizontalSpacer_8;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;

    void setupUi(QWidget *ballCamCtrl)
    {
        if (ballCamCtrl->objectName().isEmpty())
            ballCamCtrl->setObjectName(QStringLiteral("ballCamCtrl"));
        ballCamCtrl->resize(408, 242);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ballCamCtrl->sizePolicy().hasHeightForWidth());
        ballCamCtrl->setSizePolicy(sizePolicy);
        ballCamCtrl->setStyleSheet(QString::fromUtf8("#label{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#ffffff;\n"
"}\n"
"#widget{\n"
"background:#2A2B2B;\n"
"}"));
        gridLayout = new QGridLayout(ballCamCtrl);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(0, 0, 0, 10);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        savePresetBtn_ = new QPushButton(ballCamCtrl);
        savePresetBtn_->setObjectName(QStringLiteral("savePresetBtn_"));
        savePresetBtn_->setMinimumSize(QSize(100, 25));
        savePresetBtn_->setMaximumSize(QSize(100, 25));
        savePresetBtn_->setStyleSheet(QString::fromUtf8("#savePresetBtn_{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"background:#ffd500;\n"
"border-radius:12px;\n"
"color:#333333;\n"
"}\n"
""));

        gridLayout->addWidget(savePresetBtn_, 6, 0, 1, 1, Qt::AlignHCenter);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

        scaleWgt_ = new QWidget(ballCamCtrl);
        scaleWgt_->setObjectName(QStringLiteral("scaleWgt_"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scaleWgt_->sizePolicy().hasHeightForWidth());
        scaleWgt_->setSizePolicy(sizePolicy1);
        scaleWgt_->setMinimumSize(QSize(20, 40));
        scaleWgt_->setMaximumSize(QSize(20, 40));
        scaleWgt_->setLayoutDirection(Qt::LeftToRight);
        scaleWgt_->setStyleSheet(QLatin1String("QWidget#scaleWgt_{\n"
"	background-color :#121212;\n"
"	border-radius:3px;\n"
"}"));
        gridLayout_8 = new QGridLayout(scaleWgt_);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_8->setContentsMargins(5, 5, -1, 5);
        bigger_ = new QPushButton(scaleWgt_);
        bigger_->setObjectName(QStringLiteral("bigger_"));
        bigger_->setMinimumSize(QSize(10, 10));
        bigger_->setMaximumSize(QSize(10, 10));
        bigger_->setStyleSheet(QLatin1String("#bigger_{\n"
"border-image:url(:/image/image/2bigger.png);\n"
"}\n"
"#bigger_:pressed{\n"
"margin:1px;\n"
"}\n"
"#bigger_:hover{\n"
"border-image:url(:/image/image/2biggerb.png);\n"
"}"));

        gridLayout_8->addWidget(bigger_, 0, 0, 1, 1);

        smaller_ = new QPushButton(scaleWgt_);
        smaller_->setObjectName(QStringLiteral("smaller_"));
        smaller_->setMinimumSize(QSize(10, 2));
        smaller_->setMaximumSize(QSize(10, 2));
        smaller_->setStyleSheet(QLatin1String("#smaller_{\n"
"border-image:url(:/image/image/2small.png);\n"
"}\n"
"#smaller_:pressed{\n"
"margin:1px;\n"
"}\n"
"#smaller_:hover{\n"
"border-image:url(:/image/image/2smallb.png);\n"
"}"));

        gridLayout_8->addWidget(smaller_, 1, 0, 1, 1);


        horizontalLayout_2->addWidget(scaleWgt_);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_10);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer_6, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        moveWgt_ = new QWidget(ballCamCtrl);
        moveWgt_->setObjectName(QStringLiteral("moveWgt_"));
        sizePolicy1.setHeightForWidth(moveWgt_->sizePolicy().hasHeightForWidth());
        moveWgt_->setSizePolicy(sizePolicy1);
        moveWgt_->setMinimumSize(QSize(50, 50));
        moveWgt_->setMaximumSize(QSize(50, 50));
        moveWgt_->setStyleSheet(QLatin1String("QWidget#moveWgt_{\n"
"	background-color :#121212;\n"
"	border-radius:25px;\n"
"}"));
        up_ = new QPushButton(moveWgt_);
        up_->setObjectName(QStringLiteral("up_"));
        up_->setGeometry(QRect(20, 0, 10, 10));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(15);
        sizePolicy2.setVerticalStretch(15);
        sizePolicy2.setHeightForWidth(up_->sizePolicy().hasHeightForWidth());
        up_->setSizePolicy(sizePolicy2);
        up_->setMinimumSize(QSize(10, 10));
        up_->setMaximumSize(QSize(10, 10));
        up_->setStyleSheet(QLatin1String("#up_{\n"
"border-image:url(:/image/image/2up.png);\n"
"}\n"
"#up_:pressed{\n"
"margin:1px;\n"
"}\n"
"#up_:hover{\n"
"border-image:url(:/image/image/2upb.png);\n"
"}"));
        left_ = new QPushButton(moveWgt_);
        left_->setObjectName(QStringLiteral("left_"));
        left_->setGeometry(QRect(0, 20, 10, 10));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(10);
        sizePolicy3.setVerticalStretch(10);
        sizePolicy3.setHeightForWidth(left_->sizePolicy().hasHeightForWidth());
        left_->setSizePolicy(sizePolicy3);
        left_->setMinimumSize(QSize(10, 10));
        left_->setMaximumSize(QSize(10, 10));
        left_->setStyleSheet(QLatin1String("#left_{\n"
"border-image:url(:/image/image/2left.png);\n"
"}\n"
"#left_:pressed{\n"
"margin:1px;\n"
"}\n"
"#left_:hover{\n"
"border-image:url(:/image/image/2leftb.png);\n"
"}"));
        right_ = new QPushButton(moveWgt_);
        right_->setObjectName(QStringLiteral("right_"));
        right_->setGeometry(QRect(40, 20, 10, 10));
        sizePolicy3.setHeightForWidth(right_->sizePolicy().hasHeightForWidth());
        right_->setSizePolicy(sizePolicy3);
        right_->setMinimumSize(QSize(10, 10));
        right_->setMaximumSize(QSize(10, 10));
        right_->setStyleSheet(QLatin1String("#right_{\n"
"border-image:url(:/image/image/2right.png);\n"
"}\n"
"#right_:pressed{\n"
"margin:1px;\n"
"}\n"
"#right_:hover{\n"
"border-image:url(:/image/image/2rightb.png);\n"
"}"));
        down_ = new QPushButton(moveWgt_);
        down_->setObjectName(QStringLiteral("down_"));
        down_->setGeometry(QRect(20, 40, 10, 10));
        sizePolicy3.setHeightForWidth(down_->sizePolicy().hasHeightForWidth());
        down_->setSizePolicy(sizePolicy3);
        down_->setMinimumSize(QSize(10, 10));
        down_->setMaximumSize(QSize(10, 10));
        down_->setStyleSheet(QLatin1String("#down_{\n"
"border-image:url(:/image/image/2down.png);\n"
"}\n"
"#down_:pressed{\n"
"margin:1px;\n"
"}\n"
"#down_:hover{\n"
"border-image:url(:/image/image/2downb.png);\n"
"}"));

        horizontalLayout_4->addWidget(moveWgt_);

        horizontalSpacer_8 = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_4, 2, 0, 1, 1);

        widget = new QWidget(ballCamCtrl);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(0, 25));
        widget->setMaximumSize(QSize(16777215, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);


        gridLayout->addWidget(widget, 1, 0, 1, 1);

        savePresetBtn_->raise();
        widget->raise();

        retranslateUi(ballCamCtrl);

        QMetaObject::connectSlotsByName(ballCamCtrl);
    } // setupUi

    void retranslateUi(QWidget *ballCamCtrl)
    {
        ballCamCtrl->setWindowTitle(QApplication::translate("ballCamCtrl", "ballCamCtrl", 0));
        savePresetBtn_->setText(QApplication::translate("ballCamCtrl", "\344\277\235\345\255\230\344\270\272\351\242\204\347\275\256\347\202\2711", 0));
        bigger_->setText(QString());
        smaller_->setText(QString());
        up_->setText(QString());
        left_->setText(QString());
        right_->setText(QString());
        down_->setText(QString());
        label->setText(QApplication::translate("ballCamCtrl", "\347\220\203\346\234\272\350\201\224\345\212\250", 0));
    } // retranslateUi

};

namespace Ui {
    class ballCamCtrl: public Ui_ballCamCtrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALLCAMCTRL_H
