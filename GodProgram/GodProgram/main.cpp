#include <Tabs/TabsManager.hpp>
#include <Subprograms/SubprogramInstancesManager.hpp>

#include "mainwindow.hpp"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    God::Subprograms::Proxy proxy;
    MainWindow w;
    God::Subprograms::SubprogramInstancesManager mngr(w.getTabWidget(), proxy );
    //God::Tabs::TabsManager tabsMngr;

    w.setCreateNewInstanceCallback(mngr.getCreateNewInstanceCallback());

    w.show();

    return a.exec();
}
