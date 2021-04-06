#ifndef MAINMDICHILD_H
#define MAINMDICHILD_H

#include <QWidget>
#include "mdichild.h"

class MainMdiChild : public QWidget
{
    Q_OBJECT

public:
    MdiChildType switchSignal;
    explicit MainMdiChild(MdiChild *TriangleSignal, MdiChild *SinSignal, MdiChild *RandomSignal, QWidget *parent = nullptr);
    ~MainMdiChild();

private:
    QTimer dataTimer;

    QVBoxLayout *mainLayout;

    MdiChild *winPointer1;
    MdiChild *winPointer2;
    MdiChild *winPointer3;
    MdiChild *winPointer4;

    QCustomPlot *customPlotMain;
    QCustomPlot *customPlotSwitch;

    void closeEvent(QCloseEvent *e);

public slots:
    void setSwitchTriangle();
    void setSwitchSin();
    void setSwitchRandom();
    void setSwitchOption();

private slots:
    void realtimeDataSlot();

signals:

};

#endif // MAINMDICHILD_H
