#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Console *console = new Console;
    this->setCentralWidget(console);
}

MainWindow::~MainWindow()
{

}
