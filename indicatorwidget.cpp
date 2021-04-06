#include "indicatorwidget.h"

IndicatorWidget::IndicatorWidget(QString setWarningMessage, QWidget *parent) : QWidget(parent), warningMessage(setWarningMessage)
{
    myState = IndicatorState::OFF;
    normalMessage = "Normal";
    label = new QLabel(this);
    label->setText(normalMessage);
    label->setAlignment(Qt::AlignCenter);

    setMinimumHeight(20);
    setMinimumWidth(100);

    setMaximumHeight(20);
    setMaximumWidth(100);
}

void IndicatorWidget::setState(IndicatorState setTo, QString from)
{
    switch(setTo)
    {
        case IndicatorState::OFF:
            qDebug()<<myState<<" "<<from;
            myState = IndicatorState::OFF;
            label -> setText(warningMessage);
            label->setStyleSheet("background-color: green");
            break;

        case IndicatorState::ON:
            qDebug()<<myState<<" "<<from;
            myState = IndicatorState::ON;
            label -> setText(normalMessage);
            label->setStyleSheet("background-color: red");
            break;
    }
    this->update();
    this->show();
}

