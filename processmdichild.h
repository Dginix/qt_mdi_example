#ifndef PROCESSMDICHILD_H
#define PROCESSMDICHILD_H

#include <QMdiSubWindow>
#include <QWidget>
#include "mdichild.h"

class ProcessMdiChild : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit ProcessMdiChild(QWidget *parent = nullptr);
    ~ProcessMdiChild();

    void setSignal(MdiChild *f_signalToProcess);

protected:
    int inter_count;

    double x_process;
    double y_process;

    double param1;

private:
    QWidget *mainWidget;

    MdiChild *signalToProcess;

    QCustomPlot *customPlot;

    QVBoxLayout *mainLayout;

    ExtendedSlider *slider1;

    QTimer dataTimer;

    void closeEvent(QCloseEvent *e);

private slots:
    void realtimeDataSlot();
    void getValueExtSlider1(double slot_val);

};

#endif // PROCESSMDICHILD_H
