#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QToolBar>
#include <QIcon>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QAction>
#include "console.h"
#include "settingdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateStatusBar();
    void clearStatusBar();

private:
    void creatActions();
    void creatMenu();
    void creatToolBar();
    void creatStatusBar();

    Console *console;
    SettingDialog *settingdialog;

    QToolBar *mainToolBar;
    QToolBar *secondToolBar;

    QMenu *menuConnection;
    QMenu *menuTools;
    QMenu *menuAbout;

    QLabel *labelConnection;
    QLabel *labelSerialportInfo;

    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionConfigure;
    QAction *actionClear;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QAction *actionQuit;
};

#endif // MAINWINDOW_H
