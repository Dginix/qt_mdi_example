#include "indicatorwidget.h"

IndicatorWidget::IndicatorWidget(QString setWarningMessage, QWidget *parent) : QWidget(parent), warningMessage(setWarningMessage)
{
    myState = IndicatorState::OFF;

    normalMessage = "Normal";

    label = new QLabel(this);
    label->setText(normalMessage);
    label->setStyleSheet("background-color: green");
    label->setAlignment(Qt::AlignCenter);

    setMinimumHeight(20);
    setMinimumWidth(100);

    setMaximumHeight(20);
    setMaximumWidth(100);
}

void IndicatorWidget::setState(IndicatorState setTo)
{
    switch(setTo)
    {
        case IndicatorState::OFF:
            myState = IndicatorState::OFF;
            label -> setText(normalMessage);
            label->setStyleSheet("background-color: green");
            break;

        case IndicatorState::ON:
            myState = IndicatorState::ON;
            label -> setText(warningMessage);
            label->setStyleSheet("background-color: red");
            break;
    }
    this->update();
    this->show();
}

