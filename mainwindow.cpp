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

    OptionSignal = new MdiChild(MdiChildType::OptionSignal);
    connect(OptionSignal, &MdiChild::warningSignal, this, &MainWindow::onWarningSignal);
    mdiArea->addSubWindow(OptionSignal);

    mainMdiChild = new MainMdiChild(TriangleSignal, SinSignal, RandomSignal, OptionSignal);
    mdiArea->addSubWindow(mainMdiChild);

    processMdiChild = new ProcessMdiChild(this);
    mdiArea->addSubWindow(processMdiChild);
    processMdiChild->setSignal(SinSignal);
}

void MainWindow::createMenu()
{
    MainMenu = menuBar()->addMenu("SCADA");

    setSignal = new QMenu("Switch signal");

    setSignal->addAction("Triangle signal", mainMdiChild, SLOT(setSwitchTriangle()));
    setSignal->addAction("Sine signal", mainMdiChild, SLOT(setSwitchSin()));
    setSignal->addAction("Random signal", mainMdiChild, SLOT(setSwitchRandom()));
    setSignal->addAction("Option signal", mainMdiChild, SLOT(setSwitchOption()));

    setActiveWindow = new QMenu("Activate window");

    QAction *triangle_activ = new QAction("Triangle signal", this);
    setActiveWindow->addAction(triangle_activ);
    connect(triangle_activ, &QAction::triggered,
            [=]() { this->myActivateWindow(MdiChildType::TriangleSignal); });

    QAction *sin_activ = new QAction("Sine signal", this);
    setActiveWindow->addAction(sin_activ);
    connect(sin_activ, &QAction::triggered,
            [=]() { this->myActivateWindow(MdiChildType::SinSignal); });

    QAction *rand_activ = new QAction("Random signal", this);
    setActiveWindow->addAction(rand_activ);
    connect(rand_activ, &QAction::triggered,
            [=]() { this->myActivateWindow(MdiChildType::RandomSignal); });

    QAction *optopn_activ = new QAction("Option signal", this);
    setActiveWindow->addAction(optopn_activ);
    connect(optopn_activ, &QAction::triggered,
            [=]() { this->myActivateWindow(MdiChildType::OptionSignal); });


    autoActivMenu = new QMenu("Set auto activation", this);

    autoSine = new QAction("Auto warning sine signal", this);
    autoSine->setCheckable(true);

    autoTriangle = new QAction("Auto warning triangle signal", this);
    autoTriangle->setCheckable(true);

    autoRandom = new QAction("Auto warning random signal", this);
    autoRandom->setCheckable(true);

    autoOption = new QAction("Auto warning option signal", this);
    autoOption->setCheckable(true);

    autoActivMenu->addAction(autoSine);
    autoActivMenu->addAction(autoTriangle);
    autoActivMenu->addAction(autoRandom);
    autoActivMenu->addAction(autoOption);

    MainMenu->addMenu(setActiveWindow);
    MainMenu->addMenu(autoActivMenu);
    MainMenu->addMenu(setSignal);
}

void MainWindow::myActivateWindow(MdiChildType childType)
{
    switch(childType)
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
            mdiArea->setActiveSubWindow(OptionSignal);
            OptionSignal->setWindowState(OptionSignal->windowState() & ~Qt::WindowMinimized);
            break;

        case MdiChildType::RandomSignal:    // 3
            mdiArea->setActiveSubWindow(RandomSignal);
            RandomSignal->setWindowState(RandomSignal->windowState() & ~Qt::WindowMinimized);
            break;
    }
}

void MainWindow::onWarningSignal(MdiChildType slotChildType, bool warnState)
{
    static bool blockWarn1 = false;
    static bool blockWarn2 = false;
    static bool blockWarn3 = false;
    static bool blockWarn4 = false;

    if(slotChildType == MdiChildType::SinSignal && warnState) blockWarn1 = true;
    if((slotChildType == MdiChildType::SinSignal && !warnState) || !autoSine->isChecked()) blockWarn1 = false;

    if(slotChildType == MdiChildType::TriangleSignal && warnState) blockWarn2 = true;
    if((slotChildType == MdiChildType::TriangleSignal && !warnState) || !autoTriangle->isChecked()) blockWarn2 = false;

    if(slotChildType == MdiChildType::RandomSignal && warnState) blockWarn3 = true;
    if((slotChildType == MdiChildType::RandomSignal && !warnState) || !autoRandom->isChecked()) blockWarn3 = false;

    if(slotChildType == MdiChildType::OptionSignal && warnState) blockWarn4 = true;
    if((slotChildType == MdiChildType::OptionSignal && !warnState) || !autoOption->isChecked()) blockWarn4 = false;

    if(blockWarn1)
    {
        myActivateWindow(MdiChildType::SinSignal);
    }

    if(blockWarn2 && !blockWarn1)
    {
        myActivateWindow(MdiChildType::TriangleSignal);
    }

    if(blockWarn3 && !blockWarn1 && !blockWarn2)
    {
        myActivateWindow(MdiChildType::RandomSignal);
    }

    if(blockWarn4 && !blockWarn1 && !blockWarn2 && !blockWarn3)
    {
        myActivateWindow(MdiChildType::OptionSignal);
    }
}

