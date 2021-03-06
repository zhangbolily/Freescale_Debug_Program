#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    console = new Console;
    console->setEnabled(false);

    settingdialog = new SettingDialog();
    settingdialog->setWindowModality(Qt::ApplicationModal);     //弹出子窗口时禁用主窗口
    settingdialog->setWindowFlags(Qt::Dialog);               //设置为子窗口

    serial = new QSerialPort();

    creatAboutMessageBox();
    creatActions();
    creatMenu();
    creatToolBar();
    creatStatusBar();

    connect(console, SIGNAL(sendData(QByteArray)),
            this, SLOT(writeData(QByteArray)));
    connect(serial, SIGNAL(readyRead()),
            this, SLOT(getData()));

    this->setMinimumSize(800, 600);     //设置窗口最小为800*600大小
    this->setWindowTitle(tr("上海理工大学 飞思卡尔赛队串口调试工具 V1.0"));
    this->setWindowIcon(QIcon(":/image/icon.png"));
    this->setWindowIconText(tr("串口调试工具"));

    this->setCentralWidget(console);
}

void MainWindow::creatActions()
{
    actionConnect = new QAction(QIcon(":/image/connect.png"), tr("连接"), this);
    actionDisconnect = new QAction(QIcon(":/image/disconnect.png"), tr("断开连接"), this);
    actionConfigure = new QAction(QIcon(":/image/gear.png"), tr("参数设置"), this);
    actionClear = new QAction(QIcon(":/image/clear.png"), tr("清屏"), this);
    actionAbout = new QAction(QIcon(":/image/about.png"), tr("关于本程序"), this);
    actionAboutQt = new QAction(QIcon(":/image/qt.png"), tr("关于Qt"), this);
    actionQuit = new QAction(QIcon(":/image/power.png"), tr("退出程序"), this);

    connect(actionConnect, SIGNAL(triggered(bool)),         //激活连接动作时，禁用和激活一些其他的动作
            this, SLOT(openSerialPort()));
//    connect(actionConnect, SIGNAL(triggered(bool)),       //在openSerialPort()函数中完成了这些操作
//            actionDisconnect, SLOT(setDisabled(bool)));
//    connect(actionConnect, SIGNAL(triggered(bool)),
//            actionConfigure, SLOT(setEnabled(bool)));
//    connect(actionConnect, SIGNAL(triggered(bool)),
//            actionQuit, SLOT(setEnabled(bool)));
//    connect(actionConnect, SIGNAL(triggered(bool)),
//            this, SLOT(updateStatusBar()));

    connect(actionDisconnect, SIGNAL(triggered(bool)),      //激活断开动作时，禁用和激活一些其他的动作
            this, SLOT(closeSerialPort()));
//    connect(actionDisconnect, SIGNAL(triggered(bool)),    //在closeSerialPort()函数中完成了这些操作
//            actionConnect, SLOT(setDisabled(bool)));
//    connect(actionDisconnect, SIGNAL(triggered(bool)),
//            actionConfigure, SLOT(setDisabled(bool)));
    connect(actionDisconnect, SIGNAL(triggered(bool)),
            actionQuit, SLOT(setDisabled(bool)));
    connect(actionDisconnect, SIGNAL(triggered(bool)),
            this, SLOT(clearStatusBar()));

    connect(actionConfigure, SIGNAL(triggered(bool)),
            settingdialog, SLOT(fillPortsInfo()));
    connect(actionConfigure, SIGNAL(triggered(bool)),
            settingdialog, SLOT(show()));

    connect(actionQuit, SIGNAL(triggered(bool)),
            this, SLOT(close()));

    connect(actionClear, SIGNAL(triggered(bool)),
            console, SLOT(clear()));

    connect(actionAbout, SIGNAL(triggered(bool)),
            about, SLOT(show()));

    connect(actionAboutQt, SIGNAL(triggered(bool)),
            qApp, SLOT(aboutQt()));
}

void MainWindow::creatMenu()
{
    menuConnection = menuBar()->addMenu(tr("连接"));
    menuTools = menuBar()->addMenu(tr("工具"));
    menuAbout = menuBar()->addMenu(tr("关于"));

    menuConnection->addAction(actionConnect);
    menuConnection->addAction(actionDisconnect);
    menuConnection->addSeparator();
    menuConnection->addAction(actionQuit);

    menuTools->addAction(actionClear);
    menuTools->addAction(actionConfigure);

    menuAbout->addAction(actionAbout);
    menuAbout->addAction(actionAboutQt);
}

void MainWindow::creatToolBar()
{
    mainToolBar = addToolBar(tr("串口功能"));
    secondToolBar = addToolBar(tr("关于"));

    mainToolBar->addAction(actionConnect);
    mainToolBar->addAction(actionDisconnect);
    mainToolBar->addAction(actionConfigure);
    mainToolBar->addAction(actionClear);
    mainToolBar->addAction(actionQuit);

    secondToolBar->addAction(actionAbout);
    secondToolBar->addAction(actionAboutQt);
}

void MainWindow::creatStatusBar()
{
    labelConnection = new QLabel(tr("未连接  "));
    labelSerialportInfo = new QLabel();

    labelConnection->setIndent(6);
    labelSerialportInfo->setIndent(6);

    statusBar()->addWidget(labelConnection);
    statusBar()->addWidget(labelSerialportInfo, 1);
}

void MainWindow::updateStatusBar()
{
    SettingDialog::Settings currentSettings = settingdialog->settings();

    labelConnection->setText(tr("已连接  "));
    labelSerialportInfo->setText(tr("串口:%1    波特率:%2    数据位:%3    校验位:%4    停止位:%5    流控制:%6")
                                 .arg(currentSettings.name)
                                 .arg(currentSettings.baudRate)
                                 .arg(currentSettings.dataBits)
                                 .arg(currentSettings.parity)
                                 .arg(currentSettings.stopBits)
                                 .arg(currentSettings.flowControl));
}

void MainWindow::clearStatusBar()
{
    labelConnection->setText(tr("未连接  "));
    labelSerialportInfo->clear();
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    console->setEnabled(false);
    actionConnect->setEnabled(true);
    actionDisconnect->setEnabled(false);
    actionConfigure->setEnabled(true);
    actionQuit->setEnabled(true);
}

void MainWindow::openSerialPort()
{
    SettingDialog::Settings p = settingdialog->settings();
    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(p.dataBits);
    serial->setParity(p.parity);
    serial->setStopBits(p.stopBits);
    serial->setFlowControl(p.flowControl);
    if (serial->open(QIODevice::ReadWrite)) {
        console->setEnabled(true);
        console->setLocalEchoEnabled(p.localEchoEnabled);
        actionConnect->setEnabled(false);
        actionDisconnect->setEnabled(true);
        actionConfigure->setEnabled(false);
        actionQuit->setEnabled(false);
        updateStatusBar();
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        labelConnection->setText(tr("打开串口出现错误  "));
    }
}

void MainWindow::creatAboutMessageBox()
{
    about = new QMessageBox(this);
    about->setWindowTitle(tr("关于本程序"));
    about->setText(tr("这是为上海理工大学飞思卡尔赛队设计的串口调试工具。"));
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::getData()
{
    QByteArray data_r = serial->readAll();
    data_r.append('\n');

    qDebug(data_r.data());
    console->putData(data_r);
}

MainWindow::~MainWindow()
{

}
