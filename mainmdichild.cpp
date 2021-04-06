#include "mainmdichild.h"

MainMdiChild::~MainMdiChild()
{
    delete customPlotMain;
    delete customPlotSwitch;
}

void MainMdiChild::closeEvent(QCloseEvent *e)
{
    e->ignore();
}

MainMdiChild::MainMdiChild(MdiChild *TriangleSignal, MdiChild *SinSignal, MdiChild *RandomSignal, MdiChild *OptionSignal, QWidget *parent) : QWidget(parent),
    winPointer1(TriangleSignal), winPointer2(SinSignal), winPointer3(RandomSignal), winPointer4(OptionSignal)
{
    this->setMinimumSize(400, 600);
    this->setWindowTitle("Main Window");
    switchSignal = MdiChildType::TriangleSignal;

    mainLayout = new QVBoxLayout(this);

    customPlotMain = new QCustomPlot(this);
    customPlotMain->setObjectName(QString::fromUtf8("main plot"));

    customPlotMain->addGraph();
    customPlotMain->graph(0)->setPen(QPen(Qt::black));

    customPlotMain->addGraph();
    customPlotMain->graph(1)->setPen(QPen(Qt::red));

    customPlotMain->addGraph();
    customPlotMain->graph(2)->setPen(QPen(Qt::green));

    customPlotMain->addGraph();
    customPlotMain->graph(3)->setPen(QPen(Qt::blue));

    customPlotMain->axisRect()->setupFullAxesBox();
    customPlotMain->show();

    customPlotSwitch = new QCustomPlot(this);
    customPlotSwitch->setObjectName(QString::fromUtf8("switch plot"));

    customPlotSwitch->addGraph();
    customPlotSwitch->graph(0)->setPen(QPen(Qt::black));

    mainLayout->addWidget(customPlotMain);
    mainLayout->addWidget(customPlotSwitch);
    setLayout(mainLayout);

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(50); // Interval 0 means to refresh as fast as possible
                          // in msec
}

void MainMdiChild::realtimeDataSlot()
{

    customPlotMain->graph(0)->addData(winPointer1->x_data, winPointer1->y_data);
    customPlotMain->graph(1)->addData(winPointer2->x_data, winPointer2->y_data);
    customPlotMain->graph(2)->addData(winPointer3->x_data, winPointer3->y_data);
    customPlotMain->graph(3)->addData(winPointer4->x_data, winPointer4->y_data);

    customPlotMain->xAxis->setRange(winPointer3->x_data, 10, Qt::AlignRight);
    customPlotMain->yAxis->setRange(-1, 10, Qt::AlignBottom);

    double x_switch = 0;
    double y_switch = 0;

    switch(switchSignal)
    {
        case MdiChildType::TriangleSignal:  x_switch = winPointer1->x_data; y_switch = winPointer1->y_data; break;
        case MdiChildType::SinSignal:       x_switch = winPointer2->x_data; y_switch = winPointer2->y_data; break;
        case MdiChildType::RandomSignal:    x_switch = winPointer3->x_data; y_switch = winPointer3->y_data; break;
        case MdiChildType::OptionSignal:    x_switch = winPointer4->x_data; y_switch = winPointer4->y_data; break;;
    }

    customPlotSwitch->graph(0)->addData(x_switch, y_switch);

    customPlotSwitch->xAxis->setRange(x_switch, 10, Qt::AlignRight);
    customPlotSwitch->yAxis->setRange(-1, 10, Qt::AlignBottom);

    customPlotMain->replot();
    customPlotSwitch->replot();
}

void MainMdiChild::setSwitchTriangle()
{
    switchSignal = MdiChildType::TriangleSignal;
}

void MainMdiChild::setSwitchSin()
{
    switchSignal = MdiChildType::SinSignal;
}

void MainMdiChild::setSwitchRandom()
{
    switchSignal = MdiChildType::RandomSignal;
}

void MainMdiChild::setSwitchOption()
{
    switchSignal = MdiChildType::OptionSignal;
}


