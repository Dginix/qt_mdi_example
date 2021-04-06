#include "datathread.h"

#include <QDebug>

DataThread::DataThread(MdiChildType signalType)
{
    x = 0;
    y = 0;
    step = 0.05;
    param1 = 1.0;
    param2 = 1.0;
    mySignalType = signalType;
}

void DataThread::run()
{
    while(1)
    {
        x+=step;

        switch(mySignalType)
        {
            case MdiChildType::TriangleSignal:  y = triangle_signal(x, param1, param2); break;
            case MdiChildType::SinSignal:       y = sin_signal(x, param1, param2); break;
            case MdiChildType::RandomSignal:    y = random_signal(param1, param2); break;
            case MdiChildType::OptionSignal:    y = sin_signal(x, param1, param2); break;
        }

        emit valueChanged(x, y);
        this->msleep(50);
    }
}

double DataThread::sin_signal(double x, double ampl, double period)
{
    return ampl * sin(2.0 * M_PI * x * 1.0/period);
}

double DataThread::triangle_signal(double x, double ampl, double period)
{
    double y = ampl/(M_PI) * asin(cos(2 * M_PI * x * 1.0/period));
    return y;
}

double DataThread::random_signal(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

void DataThread::getStep(double fStep)
{
    step = fStep;
}

void DataThread::getParam1(double fparam1)
{
    param1 = fparam1;
}
void DataThread::getParam2(double fparam2)
{
    param1 = fparam2;
}

