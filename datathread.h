#ifndef DATATHREAD_H
#define DATATHREAD_H

#include <QThread>
#include <QString>
#include "mdichildtype.h"
#include "math.h"

class DataThread : public QThread
{
    Q_OBJECT

public:
    explicit DataThread(MdiChildType signalType);
    void run();

    double sin_signal(double x, double ampl, double period);
    double triangle_signal(double x, double ampl, double period);
    double random_signal(double min, double max);

signals:
    void valueChanged(double, double);

private:
    double x;
    double y;

    double param1;
    double param2;

    double step;
    MdiChildType mySignalType;

public slots:
    void getStep(double);
    void getParam1(double);
    void getParam2(double);
};

#endif // DATATHREAD_H
