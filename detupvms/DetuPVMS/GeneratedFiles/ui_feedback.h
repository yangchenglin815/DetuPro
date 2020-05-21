/********************************************************************************
** Form generated from reading UI file 'feedback.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FEEDBACK_H
#define UI_FEEDBACK_H

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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_feedback
{
public:
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *imageLabel_;
    QLabel *tipLabel_;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *closeButton_;

    void setupUi(QDialog *feedback)
    {
        if (feedback->objectName().isEmpty())
            feedback->setObjectName(QStringLiteral("feedback"));
        feedback->resize(339, 41);
        feedback->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"background:#eeeeee;\n"
"border-radius:4px;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"color:#323434;\n"
"text-align:center;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(feedback);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(feedback);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        imageLabel_ = new QLabel(widget);
        imageLabel_->setObjectName(QStringLiteral("imageLabel_"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageLabel_->sizePolicy().hasHeightForWidth());
        imageLabel_->setSizePolicy(sizePolicy);
        imageLabel_->setMinimumSize(QSize(22, 22));
        imageLabel_->setMaximumSize(QSize(22, 22));

        horizontalLayout->addWidget(imageLabel_);

        tipLabel_ = new QLabel(widget);
        tipLabel_->setObjectName(QStringLiteral("tipLabel_"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tipLabel_->sizePolicy().hasHeightForWidth());
        tipLabel_->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(tipLabel_);

        horizontalSpacer_2 = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        closeButton_ = new QPushButton(widget);
        closeButton_->setObjectName(QStringLiteral("closeButton_"));
        closeButton_->setMinimumSize(QSize(16, 16));
        closeButton_->setMaximumSize(QSize(16, 16));
        closeButton_->setStyleSheet(QLatin1String("#closeButton_{\n"
"border-image:url(:/image/image/bubblex.png);\n"
"}\n"
"#closeButton_:pressed{\n"
"margin:1px;\n"
"}"));

        horizontalLayout->addWidget(closeButton_);


        horizontalLayout_2->addWidget(widget);


        retranslateUi(feedback);

        QMetaObject::connectSlotsByName(feedback);
    } // setupUi

    void retranslateUi(QDialog *feedback)
    {
        feedback->setWindowTitle(QString());
        imageLabel_->setText(QString());
        tipLabel_->setText(QString());
        closeButton_->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class feedback: public Ui_feedback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FEEDBACK_H
