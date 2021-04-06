#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "mdichild.h"
#include "mdichildtype.h"
#include "mainmdichild.h"

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
    QMenu *setActiveWindow;
    QMenu *setSignal;
    QAction *action1;
    QAction *action2;

    MdiChild *TriangleSignal;
    MdiChild *SinSignal;
    MdiChild *RandomSignal;
    MdiChild *OptionSignal;

    MainMdiChild *mainMdiChild;

    void createMenu();
    void createMdi();

public slots:
    void onWarningSignal(MdiChildType fromChild);
    void testSlot();

};
#endif // MAINWINDOW_H
