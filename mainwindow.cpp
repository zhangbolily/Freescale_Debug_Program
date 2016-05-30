#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    console = new Console;
    settingdialog = new SettingDialog();
    settingdialog->setWindowModality(Qt::ApplicationModal);

    this->setMinimumSize(800, 600);     //设置窗口最小为800*600大小
    this->setWindowTitle(tr("上海理工大学 飞思卡尔赛队串口调试工具 V1.0"));
    this->setWindowIcon(QIcon(":/image/icon.png"));
    this->setWindowIconText(tr("串口调试工具"));

    mainToolBar = addToolBar(tr("串口功能"));
    secondToolBar = addToolBar(tr("关于"));

    menuConnection = menuBar()->addMenu(tr("连接"));
    menuTools = menuBar()->addMenu(tr("工具"));
    menuAbout = menuBar()->addMenu(tr("关于"));

    actionConnect = new QAction(QIcon(":/image/connect.png"), tr("连接"), this);
    actionDisconnect = new QAction(QIcon(":/image/disconnect.png"), tr("断开连接"), this);
    actionConfigure = new QAction(QIcon(":/image/gear.png"), tr("参数设置"), this);
    actionClear = new QAction(QIcon(":/image/clear.png"), tr("清屏"), this);
    actionAbout = new QAction(QIcon(":/image/about.png"), tr("关于本程序"), this);
    actionAboutQt = new QAction(QIcon(":/image/qt.png"), tr("关于Qt"), this);
    actionQuit = new QAction(QIcon(":/image/power.png"), tr("退出程序"), this);

    mainToolBar->addAction(actionConnect);
    mainToolBar->addAction(actionDisconnect);
    mainToolBar->addAction(actionConfigure);
    mainToolBar->addAction(actionClear);
    mainToolBar->addAction(actionQuit);

    secondToolBar->addAction(actionAbout);
    secondToolBar->addAction(actionAboutQt);

    menuConnection->addAction(actionConnect);
    menuConnection->addAction(actionDisconnect);
    menuConnection->addSeparator();
    menuConnection->addAction(actionQuit);

    menuTools->addAction(actionClear);
    menuTools->addAction(actionConfigure);

    menuAbout->addAction(actionAbout);
    menuAbout->addAction(actionAboutQt);

    connect(actionConfigure, SIGNAL(triggered(bool)),
            settingdialog, SLOT(show()));
    connect(actionQuit, SIGNAL(triggered(bool)),
            this, SLOT(close()));
    connect(actionAboutQt, SIGNAL(triggered(bool)),
            qApp, SLOT(aboutQt()));


    this->setCentralWidget(console);
}

MainWindow::~MainWindow()
{

}
