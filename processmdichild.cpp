#include "processmdichild.h"

ProcessMdiChild::~ProcessMdiChild()
{
    delete customPlot;
}

void ProcessMdiChild::closeEvent(QCloseEvent *e)
{
    e->ignore();
}

ProcessMdiChild::ProcessMdiChild(QWidget *parent) : QMdiSubWindow(parent)
{
    inter_count = 0;
    param1 = 5;

    mainWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(mainWidget);
    customPlot = new QCustomPlot(mainWidget);

    customPlot->setObjectName(QString::fromUtf8("signal"));

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::black));

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->axisRect()->setupFullAxesBox();
    customPlot->show();

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(50); // Interval 0 means to refresh as fast as possible
                          // in msec

    slider1 = new ExtendedSlider("interpolate count", 2, 100, 5, this);

    connect(slider1, SIGNAL(mySignal(double)), this, SLOT(getValueExtSlider1(double)));

    mainLayout->addWidget(customPlot);
    mainLayout->addWidget(slider1);
    mainWidget->setLayout(mainLayout);
    this->setWidget(mainWidget);
}

void ProcessMdiChild::setSignal(MdiChild *f_signalToProcess)
{
    inter_count = param1;
    signalToProcess = f_signalToProcess;
}

void ProcessMdiChild::realtimeDataSlot()
{
    static double last_x = 0;
    static double last_y = 0;

    customPlot->graph(0)->addData(signalToProcess->x_data, signalToProcess->y_data);

    inter_count++;

    if(inter_count >= param1)
    {
        inter_count = 0;
        customPlot->graph(1)->addData(last_x, last_y);
        last_x = signalToProcess->x_data;
        last_y = signalToProcess->y_data;
    }

    customPlot->xAxis->setRange(signalToProcess->x_data, 10, Qt::AlignRight);
    customPlot->yAxis->setRange(-1, 10, Qt::AlignBottom);

    customPlot->replot();
}

void ProcessMdiChild::getValueExtSlider1(double slot_val)
{
    param1 = slot_val;
}

