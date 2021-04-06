#ifndef DATATHREAD_H
#define DATATHREAD_H

#include <QThread>
#include <QString>

class DataThread : public QThread
{
    Q_OBJECT
public:
    explicit DataThread();
    void run();

signals:
    void valueChanged(double, double);

private:
    double x;
    double y;
};

#endif // DATATHREAD_H
