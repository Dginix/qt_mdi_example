#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QtDebug>

MainWindow::MainWindow()
    : mdiArea(new QMdiArea)
{
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    MdiChild *child = createMdiChild();

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
