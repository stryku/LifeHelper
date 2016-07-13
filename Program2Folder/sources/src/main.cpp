#include "mainwindow.h"
#include <ProgramInternalsCreators.h>
#include <QApplication>

#include <Windows.h>

#include <iostream>

int runQt( int argc, char *argv[] )
{
    FreeConsole();

    QApplication a( argc, argv );
    MainWindow w;

    auto internalWidgetParent = w.getWidgetContainer();

    auto internals = ProgramInternalsCreators::createLocalQt( internalWidgetParent );

    w.show();

    return a.exec();
}

int main(int argc, char *argv[])
{
    std::string choice = "qt";

    if(argc > 1)
        choice = argv[1];

    if( choice == "qt" )
        return runQt( argc, argv );
    else
        std::cerr << "Unsupported type of view.";

    return 1;
}
