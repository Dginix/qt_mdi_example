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

    TriangleSignal = new MdiChild(MdiChildType::TriangleSignal);
    connect(TriangleSignal, &MdiChild::warningSignal, this, &MainWindow::onWarningSignal);
    mdiArea->addSubWindow(TriangleSignal);

    SinSignal = new MdiChild(MdiChildType::SinSignal);
    connect(SinSignal, &MdiChild::warningSignal, this, &MainWindow::onWarningSignal);
    mdiArea->addSubWindow(SinSignal);

    RandomSignal = new MdiChild(MdiChildType::RandomSignal);
    connect(RandomSignal, &MdiChild::warningSignal, this, &MainWindow::onWarningSignal);
    mdiArea->addSubWindow(RandomSignal);

    mainMdiChild = new MainMdiChild(TriangleSignal, SinSignal, RandomSignal);
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

void MainWindow::onWarningSignal(MdiChildType fromChild)
{
    switch(fromChild)
    {
        case MdiChildType::SinSignal:   // 1
            mdiArea->setActiveSubWindow(SinSignal);
            SinSignal->setWindowState(SinSignal->windowState() & ~Qt::WindowMinimized);
            break;

        case MdiChildType::TriangleSignal:    // 2
            mdiArea->setActiveSubWindow(TriangleSignal);
            TriangleSignal->setWindowState(TriangleSignal->windowState() & ~Qt::WindowMinimized);
            break;

        case MdiChildType::OptionSignal:     // 4
//            mdiArea->setActiveSubWindow(OptionSignal);
//            OptionSignal->setWindowState(OptionSignal->windowState() & ~Qt::WindowMinimized);
            break;

        case MdiChildType::RandomSignal:    // 3
            mdiArea->setActiveSubWindow(RandomSignal);
            RandomSignal->setWindowState(RandomSignal->windowState() & ~Qt::WindowMinimized);
            break;
    }
}

void MainWindow::testSlot()
{
    qDebug()<<"bla";
}

