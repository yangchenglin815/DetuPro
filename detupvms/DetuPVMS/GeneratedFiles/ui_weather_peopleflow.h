/********************************************************************************
** Form generated from reading UI file 'weather_peopleflow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEATHER_PEOPLEFLOW_H
#define UI_WEATHER_PEOPLEFLOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_weather_peopleflow
{
public:
    QGridLayout *gridLayout;
    QPushButton *weather;

    void setupUi(QWidget *weather_peopleflow)
    {
        if (weather_peopleflow->objectName().isEmpty())
            weather_peopleflow->setObjectName(QStringLiteral("weather_peopleflow"));
        weather_peopleflow->resize(300, 236);
        gridLayout = new QGridLayout(weather_peopleflow);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        weather = new QPushButton(weather_peopleflow);
        weather->setObjectName(QStringLiteral("weather"));
        weather->setMinimumSize(QSize(232, 236));
        weather->setMaximumSize(QSize(300, 236));
        weather->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(weather, 0, 0, 1, 1);


        retranslateUi(weather_peopleflow);

        QMetaObject::connectSlotsByName(weather_peopleflow);
    } // setupUi

    void retranslateUi(QWidget *weather_peopleflow)
    {
        weather_peopleflow->setWindowTitle(QApplication::translate("weather_peopleflow", "weather_peopleflow", 0));
        weather->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class weather_peopleflow: public Ui_weather_peopleflow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEATHER_PEOPLEFLOW_H
