#include "mainwindow.h"
#include "ProgramFactory.h"
#include <QApplication>

#include <Windows.h>


int main(int argc, char *argv[])
{
    std::string choice = "qt";

    if(argc > 1)
        choice = argv[1];

    if(choice == "qt")
    {
        FreeConsole();





        QApplication a(argc, argv);
        MainWindow w;

        auto internalWidgetParent = w.getWidgetContainer();

        auto internals = ProgramFactory::createLocalQt(internalWidgetParent);

        w.show();

        return a.exec();
    }
    else if(choice == "console")
    {

    }
    else if(choice == "remote")
    {

    }

    return 1;
}
