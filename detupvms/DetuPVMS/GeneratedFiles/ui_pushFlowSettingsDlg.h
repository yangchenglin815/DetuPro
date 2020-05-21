/********************************************************************************
** Form generated from reading UI file 'pushFlowSettingsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PUSHFLOWSETTINGSDLG_H
#define UI_PUSHFLOWSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pushFlowSettingsDlg
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *titleWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *titleLabel;
    QPushButton *closeBtn;
    QStackedWidget *stackedWidget;
    QWidget *pushFlowPage;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *startBtn;
    QPushButton *cancelBtn;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *pushFlowInfoPage;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *urlLabel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *copyUrlBtn;
    QLabel *timeLabel;
    QLabel *infoLabel;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *disconnectedBtn;
    QPushButton *confirmBtn;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *pushFlowSettingsDlg)
    {
        if (pushFlowSettingsDlg->objectName().isEmpty())
            pushFlowSettingsDlg->setObjectName(QStringLiteral("pushFlowSettingsDlg"));
        pushFlowSettingsDlg->resize(520, 225);
        pushFlowSettingsDlg->setStyleSheet(QString::fromUtf8("QLabel,\n"
"QPushButton,\n"
"QComboBox{\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:12px;\n"
"}\n"
"#titleWidget{\n"
"background:rgba(255,255,255,1);\n"
"border-top-left-radius:4px;\n"
"border-top-right-radius:4px;\n"
"}\n"
"#titleLabel{\n"
"color:rgba(50,52,52,1);\n"
"}\n"
"#pushFlowPage,\n"
"#pushFlowInfoPage{\n"
"background:rgba(238,238,238,1);\n"
"border-bottom-left-radius:4px;\n"
"border-bottom-right-radius:4px;\n"
"}\n"
"\n"
"#label{\n"
"color:rgba(134,137,137,1);\n"
"}\n"
"#startBtn,\n"
"#disconnectedBtn{\n"
"border:none;\n"
"border-radius:2px;\n"
"color:rgba(50,52,52,1);\n"
"background:rgba(255,213,0,1);\n"
"}\n"
"#startBtn:pressed,\n"
"#disconnectedBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#startBtn:disabled,\n"
"#disconnectedBtn:disabled{\n"
"background:#dddddd;\n"
"}\n"
"#cancelBtn,\n"
"#confirmBtn{\n"
"border:none;\n"
"border-radius:2px;\n"
"color:rgba(50,52,52,1);\n"
"background:rgba(255,255,255,1);\n"
"}\n"
"#cancelBtn:pressed,\n"
"#confirmBtn:pressed{\n"
"mar"
                        "gin:1px;\n"
"}\n"
"#closeBtn{\n"
"border-image: url(:/image/image/popupx.png);\n"
"}\n"
"#closeBtn:pressed{\n"
"margin:1px;\n"
"}\n"
"#comboBox{\n"
"border:1px solid #C3C9C9;\n"
"border-radius:2px;\n"
"padding-left:6px;\n"
"min-height:28px;\n"
"}\n"
"#comboBox:editable{\n"
"background:white;\n"
"}\n"
"#comboBox:!editable,#comboBox::drop-down:editable{\n"
" background: qlineargradient(\n"
"  x1: 0, y1: 0, x2: 0, y2: 1,\n"
"  stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"  stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\n"
"}\n"
"#comboBox:!editable:on, #comboBox::drop-down:editable:on {\n"
" background: qlineargradient(\n"
"  x1: 0, y1: 0, x2: 0, y2: 1,\n"
"  stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\n"
"  stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\n"
"}\n"
"#comboBox:on{ \n"
"  padding-top: 3px;\n"
"  padding-left: 4px;\n"
"}\n"
"#comboBox::drop-down{\n"
"      subcontrol-origin: padding;\n"
"      subcontrol-position: top right;\n"
"      width: 20px;\n"
"\n"
"      border-left-width: 1px;\n"
"      border-left-color: darkgray;\n"
" "
                        "     border-left-style: solid;\n"
"      border-top-right-radius: 3px; \n"
"      border-bottom-right-radius: 3px;\n"
"}\n"
"#comboBox::down-arrow{\n"
"      image: url(:/image/image/arrow.png);\n"
"}\n"
"\n"
"#comboBox::down-arrow:on{\n"
"      top: 1px;\n"
"      left: 1px;\n"
"}\n"
"#comboBox QAbstractItemView{\n"
"      border: 2px solid darkgray;\n"
"      selection-background-color: lightgray;\n"
"}\n"
"#comboBox QAbstractItemView::item{\n"
"      min-height:28px;\n"
"}\n"
"#label_2,\n"
"#urlLabel,\n"
"#infoLabel,\n"
"#stateLabel,\n"
"#timeLabel{\n"
"color:rgba(102,102,102,1);\n"
"}\n"
"#copyUrlBtn{\n"
"border:none;\n"
"background:rgba(70,153,0,0.16);\n"
"border-radius:3px;\n"
"color:rgba(70,153,0,1);\n"
"}\n"
"#copyUrlBtn:pressed{\n"
"margin:1px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(pushFlowSettingsDlg);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleWidget = new QWidget(pushFlowSettingsDlg);
        titleWidget->setObjectName(QStringLiteral("titleWidget"));
        titleWidget->setMinimumSize(QSize(0, 32));
        titleWidget->setMaximumSize(QSize(16777215, 32));
        horizontalLayout = new QHBoxLayout(titleWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(17, -1, -1, -1);
        titleLabel = new QLabel(titleWidget);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));

        horizontalLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);

        closeBtn = new QPushButton(titleWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setMinimumSize(QSize(8, 7));
        closeBtn->setMaximumSize(QSize(8, 7));

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addWidget(titleWidget);

        stackedWidget = new QStackedWidget(pushFlowSettingsDlg);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        pushFlowPage = new QWidget();
        pushFlowPage->setObjectName(QStringLiteral("pushFlowPage"));
        gridLayout = new QGridLayout(pushFlowPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(16);
        gridLayout->setContentsMargins(90, 40, 90, 35);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(pushFlowPage);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(pushFlowPage);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMinimumSize(QSize(280, 30));
        comboBox->setMaximumSize(QSize(280, 28));
        comboBox->setEditable(true);

        horizontalLayout_2->addWidget(comboBox);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(20);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        startBtn = new QPushButton(pushFlowPage);
        startBtn->setObjectName(QStringLiteral("startBtn"));
        startBtn->setMinimumSize(QSize(80, 26));
        startBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_3->addWidget(startBtn);

        cancelBtn = new QPushButton(pushFlowPage);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));
        cancelBtn->setMinimumSize(QSize(80, 26));
        cancelBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_3->addWidget(cancelBtn);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        stackedWidget->addWidget(pushFlowPage);
        pushFlowInfoPage = new QWidget();
        pushFlowInfoPage->setObjectName(QStringLiteral("pushFlowInfoPage"));
        gridLayout_2 = new QGridLayout(pushFlowInfoPage);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(60, 25, 49, 35);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(pushFlowInfoPage);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(64, 21));
        label_2->setMaximumSize(QSize(64, 21));

        horizontalLayout_4->addWidget(label_2);

        urlLabel = new QLabel(pushFlowInfoPage);
        urlLabel->setObjectName(QStringLiteral("urlLabel"));
        urlLabel->setMinimumSize(QSize(0, 21));
        urlLabel->setMaximumSize(QSize(16777215, 21));

        horizontalLayout_4->addWidget(urlLabel, 0, Qt::AlignLeft);

        horizontalSpacer_3 = new QSpacerItem(14, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        copyUrlBtn = new QPushButton(pushFlowInfoPage);
        copyUrlBtn->setObjectName(QStringLiteral("copyUrlBtn"));
        copyUrlBtn->setMinimumSize(QSize(60, 21));
        copyUrlBtn->setMaximumSize(QSize(60, 21));

        horizontalLayout_4->addWidget(copyUrlBtn);


        gridLayout_2->addLayout(horizontalLayout_4, 0, 0, 1, 1);

        timeLabel = new QLabel(pushFlowInfoPage);
        timeLabel->setObjectName(QStringLiteral("timeLabel"));

        gridLayout_2->addWidget(timeLabel, 1, 0, 1, 1);

        infoLabel = new QLabel(pushFlowInfoPage);
        infoLabel->setObjectName(QStringLiteral("infoLabel"));

        gridLayout_2->addWidget(infoLabel, 2, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        disconnectedBtn = new QPushButton(pushFlowInfoPage);
        disconnectedBtn->setObjectName(QStringLiteral("disconnectedBtn"));
        disconnectedBtn->setMinimumSize(QSize(80, 26));
        disconnectedBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_5->addWidget(disconnectedBtn);

        confirmBtn = new QPushButton(pushFlowInfoPage);
        confirmBtn->setObjectName(QStringLiteral("confirmBtn"));
        confirmBtn->setMinimumSize(QSize(80, 26));
        confirmBtn->setMaximumSize(QSize(80, 26));

        horizontalLayout_5->addWidget(confirmBtn);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout_5, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        stackedWidget->addWidget(pushFlowInfoPage);

        verticalLayout->addWidget(stackedWidget);


        retranslateUi(pushFlowSettingsDlg);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(pushFlowSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *pushFlowSettingsDlg)
    {
        pushFlowSettingsDlg->setWindowTitle(QApplication::translate("pushFlowSettingsDlg", "Dialog", 0));
        titleLabel->setText(QApplication::translate("pushFlowSettingsDlg", "\346\216\250\346\265\201\350\256\276\347\275\256", 0));
        closeBtn->setText(QString());
        label->setText(QApplication::translate("pushFlowSettingsDlg", "\346\216\250\346\265\201\345\234\260\345\235\200", 0));
        startBtn->setText(QApplication::translate("pushFlowSettingsDlg", "\345\274\200\345\220\257", 0));
        cancelBtn->setText(QApplication::translate("pushFlowSettingsDlg", "\345\217\226\346\266\210", 0));
        label_2->setText(QApplication::translate("pushFlowSettingsDlg", "\346\216\250\346\265\201\345\234\260\345\235\200:", 0));
        urlLabel->setText(QApplication::translate("pushFlowSettingsDlg", "http://www.fevte.com/3d/C4D/?zod=&pag...", 0));
        copyUrlBtn->setText(QApplication::translate("pushFlowSettingsDlg", "\345\244\215\345\210\266\345\234\260\345\235\200", 0));
        timeLabel->setText(QApplication::translate("pushFlowSettingsDlg", "\346\216\250\346\265\201\346\227\266\351\225\277:  00:00:00", 0));
        infoLabel->setText(QApplication::translate("pushFlowSettingsDlg", "\346\216\250\346\265\201\345\210\206\350\276\250\347\216\2071920x960 @20fps \347\240\201\347\216\2075000kbps", 0));
        disconnectedBtn->setText(QApplication::translate("pushFlowSettingsDlg", "\346\226\255\345\274\200", 0));
        confirmBtn->setText(QApplication::translate("pushFlowSettingsDlg", "\347\241\256\350\256\244", 0));
    } // retranslateUi

};

namespace Ui {
    class pushFlowSettingsDlg: public Ui_pushFlowSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PUSHFLOWSETTINGSDLG_H
