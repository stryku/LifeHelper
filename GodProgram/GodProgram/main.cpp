#include "Tabs/TabsManager.hpp"
#include "Subprograms/SubprogramInstancesManager.hpp"
#include "communication/Proxy.hpp"
#include "communication/ChannelFactory.hpp"

#include "mainwindow.hpp"


#include <QApplication>

int main(int argc, char *argv[])
{
    using Factory = Common::Communication::ChannelFactory;
    using Sub = Common::Communication::xSubscriberChannel;
    using Pub = Common::Communication::xPublisherChannel;

    using ProxyGodToSubprogram = God::Communication::Proxy<Sub, Pub,
        God::Communication::detail::AddressProvider::GodToSubprogram,
        God::Communication::detail::ZmqFrontendBackendBinder>;

    using ProxySubprogramToGod = God::Communication::Proxy<Sub, Pub,
        God::Communication::detail::AddressProvider::SubprogramToGod,
        God::Communication::detail::ZmqFrontendBackendBinder>;


    QApplication a(argc, argv);
    ProxyGodToSubprogram god2Sub{ Factory::create<Sub>(),
                                  Factory::create<Pub>() };
    ProxySubprogramToGod sub2God{ Factory::create<Sub>(),
                                  Factory::create<Pub>() };

    god2Sub.startBindings();
    sub2God.startBindings();

    MainWindow w;
    God::Subprograms::SubprogramInstancesManager<ProxyGodToSubprogram, 
                                                 ProxySubprogramToGod> mngr{ w.getTabWidget(),
                                                                             std::move(god2Sub),
                                                                             std::move(sub2God) };
    //God::Tabs::TabsManager tabsMngr;

    w.setCreateNewInstanceCallback(mngr.getCreateNewInstanceCallback());

    w.show();

    return a.exec();
}
