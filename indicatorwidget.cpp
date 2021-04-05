#include "indicatorwidget.h"

IndicatorWidget::IndicatorWidget(QString setWarningMessage, QWidget *parent) : QWidget(parent), warningMessage(setWarningMessage)
{
    myState = IndicatorState::OFF;
    normalMessage = "Normal";

    setMinimumWidth(300);
    setMinimumHeight(60);

    setMaximumHeight(300);
    setMaximumWidth(60);
    messageToShow = &warningMessage;
}

void IndicatorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if (myState == IndicatorState::OFF) painter.setBrush(Qt::green);
    if (myState == IndicatorState::ON) painter.setBrush(Qt::red);
    painter.drawEllipse(0, 0, 20, 20);
    painter.drawText(40, 15, *messageToShow);
}

void IndicatorWidget::setState(IndicatorState setTo)
{
    switch(setTo)
    {
        case IndicatorState::OFF:
            myState = IndicatorState::OFF;
            messageToShow = &warningMessage;
            break;

        case IndicatorState::ON:
            myState = IndicatorState::ON;
            messageToShow = &normalMessage;
            break;
    }
    this->repaint();
}

