#include <Tabs/TabsManager.hpp>

#include "mainwindow.hpp"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    God::Tabs::TabsManager tabsMngr;

    MainWindow w(tabsMngr);
    w.show();

    return a.exec();
}
