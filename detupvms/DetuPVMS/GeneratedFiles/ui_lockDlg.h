/********************************************************************************
** Form generated from reading UI file 'lockDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCKDLG_H
#define UI_LOCKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_lockDlg
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *imageLabel;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *lockDlg)
    {
        if (lockDlg->objectName().isEmpty())
            lockDlg->setObjectName(QStringLiteral("lockDlg"));
        lockDlg->resize(353, 53);
        lockDlg->setStyleSheet(QString::fromUtf8("QDialog{\n"
"background:#eeeeee;\n"
"border-radius:5px;\n"
"}\n"
"QLabel{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:14px;\n"
"color:#323434;\n"
"text-align:center;\n"
"}"));
        horizontalLayout = new QHBoxLayout(lockDlg);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        imageLabel = new QLabel(lockDlg);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setMinimumSize(QSize(22, 22));
        imageLabel->setMaximumSize(QSize(22, 22));

        horizontalLayout->addWidget(imageLabel);

        label = new QLabel(lockDlg);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(69, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(lockDlg);

        QMetaObject::connectSlotsByName(lockDlg);
    } // setupUi

    void retranslateUi(QDialog *lockDlg)
    {
        lockDlg->setWindowTitle(QApplication::translate("lockDlg", "Dialog", 0));
        imageLabel->setText(QString());
        label->setText(QApplication::translate("lockDlg", "\347\224\250\346\210\267\345\267\262\351\224\201\345\256\232\357\274\214\347\202\271\346\210\221\350\247\243\351\224\201", 0));
    } // retranslateUi

};

namespace Ui {
    class lockDlg: public Ui_lockDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCKDLG_H
