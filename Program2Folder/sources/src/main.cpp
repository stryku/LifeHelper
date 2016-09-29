#include "mainwindow.h"
#include "utils/log.hpp"
#include "ProgramInternalsCreators.h"

#include <QApplication>

#ifdef WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <thread>
#include <chrono>

int runQt( int argc, char *argv[] )
{
    LOG_FILE("Running qt");

#ifdef WIN32 //todo
    //FreeConsole();
#endif

    QApplication a( argc, argv );
    MainWindow w;

    auto internalWidgetParent = w.getWidgetContainer();

    auto internals = ProgramInternalsCreators::Creator::createLocalQt( internalWidgetParent );

    w.show();

    return a.exec();
}

struct RemoteArgs
{
    std::string address;
    std::string modelId;
};

RemoteArgs parseRemoteArgs(int argc, char *argv[])
{
    return {
        argv[2],
        argv[3]
    };
}

void runRemote(int argc, char *argv[])
{
    LOG_FILE("Running remote");

#ifdef WIN32 //todo
    //FreeConsole();
#endif
    auto args = parseRemoteArgs(argc, argv);

    auto instance = ProgramInternalsCreators::Creator::createRemote(args.address, args.modelId);
    instance.startListening(args.address);

    while (1)
        std::this_thread::sleep_for(std::chrono::seconds(123));


}

int main(int argc, char *argv[])
{
    LOG_FILE("argc: " << argc);

    for (size_t i = 0; i < argc; ++i)
        LOG_FILE("argv[" << i << "]: " << argv[i]);

    std::string choice = "qt";

    if(argc > 1)
        choice = argv[1];

    LOG_FILE("choice: " << choice);

    if (choice == "qt")
        return runQt(argc, argv);
    else if (choice == "remote")
        return runRemote(argc, argv);
    else
        std::cerr << "Unsupported type of view.";

    return 1;
}
