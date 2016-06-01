#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("plastique");
    QApplication a(argc, argv);

//    QFile qss("stylesheet.qss");
//    qss.open(QFile::ReadOnly);
//    a.setStyleSheet(qss.readAll());
//    qss.close();

    MainWindow w;
    w.show();

    return a.exec();
}
