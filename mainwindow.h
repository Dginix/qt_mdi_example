#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "mdichild.h"
#include "mdichildtype.h"

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

    QMenu *windowMenu;
    QAction *do_smth_1;
    QAction *do_smth_2;

    MdiChild *createMdiChild();

};
#endif // MAINWINDOW_H
