#include "datathread.h"

#include <QDebug>

DataThread::DataThread()
{
}

void DataThread::run()
{
    while(1)
    {
        x+=0.02;
        y+=0.01;
        emit valueChanged(x, y);
        this->msleep(100);
    }
}
