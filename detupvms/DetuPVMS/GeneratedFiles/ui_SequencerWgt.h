/********************************************************************************
** Form generated from reading UI file 'SequencerWgt.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEQUENCERWGT_H
#define UI_SEQUENCERWGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SequencerWgt
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *SequencerWgt)
    {
        if (SequencerWgt->objectName().isEmpty())
            SequencerWgt->setObjectName(QStringLiteral("SequencerWgt"));
        SequencerWgt->resize(92, 64);
        SequencerWgt->setStyleSheet(QLatin1String("#SequencerWgt{\n"
"background:rgba(0,0,0,0.70);\n"
"}"));
        gridLayout = new QGridLayout(SequencerWgt);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(SequencerWgt);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(25, 32));
        pushButton->setMaximumSize(QSize(25, 32));
        pushButton->setStyleSheet(QLatin1String("#pushButton{\n"
"border-image:url(:/image/image/Sequencer_next.png);\n"
"}\n"
"#pushButton:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(SequencerWgt);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(25, 32));
        pushButton_2->setMaximumSize(QSize(25, 32));
        pushButton_2->setStyleSheet(QLatin1String("#pushButton_2{\n"
"border-image:url(:/image/image/Sequencer_prev.png);\n"
"}\n"
"#pushButton_2:pressed{\n"
"margin:1px;\n"
"}"));

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);


        retranslateUi(SequencerWgt);

        QMetaObject::connectSlotsByName(SequencerWgt);
    } // setupUi

    void retranslateUi(QWidget *SequencerWgt)
    {
        SequencerWgt->setWindowTitle(QApplication::translate("SequencerWgt", "SequencerWgt", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SequencerWgt: public Ui_SequencerWgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEQUENCERWGT_H
