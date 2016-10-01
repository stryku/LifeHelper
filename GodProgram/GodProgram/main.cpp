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

   /* auto callback = [](const std::string &msg)
    {
        LOG_FILE("PROXY CAPTURE: " << msg);
    };*/

    /*auto loop = []
    {
        auto pub = Factory::create<Common::Communication::PublisherChannel>();
        auto sub = Factory::createSubscriber<Common::Communication::SubscriberChannel>("1");
        pub.bind("tcp://127.0.0.1:1111");
        sub.bind("inproc://simandero:1111");

        for (;;)
        {
            zmq::message_t msg;
            sub.recv(msg);
            pub.send(msg);
            std::this_thread::sleep_for(std::chrono::seconds{ 1 });
        }
    };

    auto thread = std::thread{ loop };*/

   /* auto pusher = Factory::create<Common::Communication::PusherChannel>();

    pusher.bind("inproc://proxycapture:1111");

    Common::Communication::ProxyCapturer<Common::Communication::PullerChannel, Factory> proxyCapturer(callback);

    proxyCapturer.start("inproc://proxycapture:1111");*/

    

    QApplication a(argc, argv);
    ProxyGodToSubprogram god2Sub{ Factory::create<Sub>(),
                                  Factory::create<Pub>() };
    ProxySubprogramToGod sub2God{ Factory::create<Sub>(),
                                  Factory::create<Pub>() };


    //pusher.send("siema");
    LOG_FILE("god2Sub.startBindings");
    god2Sub.startBindings();

    LOG_FILE("sub2God.startBindings");
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
