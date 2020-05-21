/********************************************************************************
** Form generated from reading UI file 'calendarWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARWIDGET_H
#define UI_CALENDARWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calendarWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QCalendarWidget *calendar;

    void setupUi(QWidget *calendarWidget)
    {
        if (calendarWidget->objectName().isEmpty())
            calendarWidget->setObjectName(QStringLiteral("calendarWidget"));
        calendarWidget->resize(248, 210);
        calendarWidget->setMinimumSize(QSize(210, 210));
        calendarWidget->setMaximumSize(QSize(248, 210));
        horizontalLayout = new QHBoxLayout(calendarWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        calendar = new QCalendarWidget(calendarWidget);
        calendar->setObjectName(QStringLiteral("calendar"));
        calendar->setStyleSheet(QString::fromUtf8("QToolButton#qt_calendar_prevmonth,QToolButton#qt_calendar_nextmonth,QToolButton#qt_calendar_monthbutton,QToolButton#qt_calendar_yearbutton{\n"
"border:0px solid #000000;\n"
"border-radius:3px;\n"
"margin:3px 3px 3px 3px;\n"
"padding:3px;\n"
"background-color:rgba(0,0,0,0);\n"
"}\n"
"QToolButton#qt_calendar_monthbutton{\n"
"font:14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#0045d0;\n"
"}\n"
"QToolButton#qt_calendar_yearbutton{\n"
"font:14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color:#000000;\n"
"}\n"
"QToolButton#qt_calendar_prevmonth:hover,QToolButton#qt_calendar_nextmonth:hover,QToolButton#qt_calendar_monthbutton:hover,QToolButton#qt_calendar_yearbutton:hover,QToolButton#qt_calendar_prevmonth:pressed,QToolButton#qt_calendar_nextmonth:pressed,QToolButton#qt_calendar_monthbutton:pressed,QToolButton#qt_calendar_yearbutton:pressed{\n"
"border:1px solid #D8D8D8;\n"
"}\n"
"\n"
"QCalendarWidget QSpinBox#qt_calendar_yearedit{\n"
"margin:3px 3px 3px 3px;\n"
"padding:0px -7p"
                        "x 0px 0px;\n"
"}\n"
"\n"
"QDateEdit QCalendarWidget QSpinBox#qt_calendar_yearedit,QDateTimeEdit QCalendarWidget QSpinBox#qt_calendar_yearedit{\n"
"padding:0px -2px 0px 0px;\n"
"}\n"
"\n"
"QCalendarWidget QToolButton::menu-indicator{\n"
"image:None;\n"
"}\n"
"\n"
"QCalendarWidget QTableView{\n"
"border-width:0px;\n"
"\n"
"}\n"
"\n"
"QCalendarWidget QWidget#qt_calendar_navigationbar{\n"
"border:1px solid #575757;\n"
"border-width:1px 1px 0px 1px;\n"
"background:#bebebe;\n"
"}"));
        calendar->setGridVisible(false);
        calendar->setSelectionMode(QCalendarWidget::SingleSelection);
        calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout->addWidget(calendar);


        retranslateUi(calendarWidget);

        QMetaObject::connectSlotsByName(calendarWidget);
    } // setupUi

    void retranslateUi(QWidget *calendarWidget)
    {
        calendarWidget->setWindowTitle(QApplication::translate("calendarWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class calendarWidget: public Ui_calendarWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARWIDGET_H
