#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Console *console = new Console;
    SettingDialog *settingdialog = new SettingDialog();
    this->setCentralWidget(console);
    settingdialog->show();
}

MainWindow::~MainWindow()
{

}
