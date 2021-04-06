#include "datathread.h"

#include <QDebug>

DataThread::DataThread(MdiChildType signalType)
{
    x = 0;
    y = 0;
    step = 0.005;
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
            case MdiChildType::OptionSignal:    y = option_signal(x, param1, param2); break;
        }

        emit valueChanged(x, y);
        this->msleep(20);
    }
}

double DataThread::sin_signal(double x, double ampl, double period)
{
    return ampl * sin(x * 2.0 * M_PI * 1.0 / period);
}

double DataThread::triangle_signal(double x, double ampl, double period)
{
    return (ampl/(M_PI_2)) * asin(cos(2.0 * M_PI * x * 1.0 / period));
}

double DataThread::random_signal(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

double DataThread::option_signal(double x, double ampl, double period)
{
    double y;
    static double add = 0;
    double freq = 1.0 / period;

    if(x - add >= period/4.0)
    {
        add += period/4.0;
    }

    y =  ampl * sin((x - add) * 2.0 * M_PI * freq);

    return y;
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
    param2 = fparam2;
}

