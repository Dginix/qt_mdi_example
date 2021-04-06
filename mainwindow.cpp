#include "mainwindow.h"
#include "mainwindow.h"
#include "qcustomplot.h"
#include <QtDebug>
#include <QThread>

MainWindow::MainWindow()
    : mdiArea(new QMdiArea)
{
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    MdiChild *child = new MdiChild(MdiChildType::SinSignal);
    mdiArea->addSubWindow(child);

    MdiChild *child2 = new MdiChild(MdiChildType::TriangleSignal);
    mdiArea->addSubWindow(child2);

    MdiChild *child3 = new MdiChild(MdiChildType::RandomSignal);
    mdiArea->addSubWindow(child3);

    do_smth_1 = new QAction(tr("&do_smth_1"), this);
    do_smth_1->setShortcuts(QKeySequence::New);
    do_smth_1->setStatusTip(tr("Create a new file"));

    windowMenu = menuBar()->addMenu(tr("&SCADA"));
    windowMenu->addAction(do_smth_1);
}

MainWindow::~MainWindow()
{
}

MdiChild *MainWindow::createMdiChild()
{
    MdiChild *child = new MdiChild;
    mdiArea->addSubWindow(child);
    return child;
}
