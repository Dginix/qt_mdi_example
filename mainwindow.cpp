#include "mainwindow.h"
#include "qcustomplot.h"
#include <QtDebug>
#include <QThread>

MainWindow::~MainWindow()
{

}

MainWindow::MainWindow()
    : mdiArea(new QMdiArea)
{
    createMdi();
    createMenu();
}

void MainWindow::createMdi()
{
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    child1 = new MdiChild(MdiChildType::TriangleSignal);
    mdiArea->addSubWindow(child1);

    child2 = new MdiChild(MdiChildType::SinSignal);
    mdiArea->addSubWindow(child2);

    child3 = new MdiChild(MdiChildType::RandomSignal);
    mdiArea->addSubWindow(child3);

    mainMdiChild = new MainMdiChild(child1, child2, child3);
    mdiArea->addSubWindow(mainMdiChild);
}

void MainWindow::createMenu()
{
    MainMenu = menuBar()->addMenu("SCADA");

    setSignal = new QMenu("Switch signal");

    setSignal->addAction("Triangle signal", mainMdiChild, SLOT(setSwitchTriangle()));
    setSignal->addAction("Sine signal", mainMdiChild, SLOT(setSwitchSin()));
    setSignal->addAction("Random signal", mainMdiChild, SLOT(setSwitchRandom()));
    setSignal->addAction("OPtion signal", mainMdiChild, SLOT(setSwitchOption()));

    setActiveWindow = new QMenu("Activate window");

    MainMenu->addMenu(setActiveWindow);
    MainMenu->addMenu(setSignal);
}


