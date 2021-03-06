#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "mdichild.h"
#include "mdichildtype.h"
#include "mainmdichild.h"
#include <functional>
#include "processmdichild.h"

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:


    MainWindow();
    ~MainWindow();
    QTimer dataTimer;

private:
    QMdiArea *mdiArea;

    QMenu *MainMenu;

    QMenu *processMenu;
    QAction *processSine;
    QAction *processTriangle;
    QAction *processRandom;
    QAction *processOption;

    QMenu *autoActivMenu;
    QAction *autoSine;
    QAction *autoTriangle;
    QAction *autoRandom;
    QAction *autoOption;

    QMenu *setActiveWindow;
    QAction *triangleActiv;
    QAction *sinActiv;
    QAction *randActiv;
    QAction *optopnActiv;

    QMenu *setSignal;
    MdiChild *TriangleSignal;
    MdiChild *SinSignal;
    MdiChild *RandomSignal;
    MdiChild *OptionSignal;

    MainMdiChild *mainMdiChild;

    ProcessMdiChild *processMdiChild;


    void createMenu();
    void createMdi();
    void myActivateWindow(MdiChildType childType);

public slots:
    void onWarningSignal(MdiChildType, bool);
};
#endif // MAINWINDOW_H
