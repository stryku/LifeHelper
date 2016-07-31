#pragma once

#include <communication/OneWayChannel.hpp>

#include <Subprograms/SubprogramSignalHandler.hpp>
#include <Subprograms/SubprogramMessagesSubscriber.hpp>
#include <Subprograms/Messages/Handlers/Program2MessageHandler.hpp>

#include <program2internals/input/SocketInputObserverSender.hpp>

#include <QTabWidget>

namespace God
{
    namespace Subprograms
    {
        template <typename TypesPack>
        class Instance
        {
        public:
            Instance(QTabWidget &tabWidget, 
                     ModelId modelId,
                     const std::string &pushAddress,
                     const std::string &subscribeAddress,
                     const std::string &subscribeStr.
                     SignalsHandler &signalHandler) :
                internals { &controller },
                view{ &tabWidget }, 
                inputPropagator{ sender },
                signalsHandler{ signalsHandler },
                messageHandler{ signalsHandler },
                messageSubscriber{ subscribeAddress, subscribeStr, messageHandler },
                modelId{ modelId }
            {
                internals.addView(&view);
                internals.addInputPropagator(&inputPropagator);

                establishConnection(pushAddress, subscribeAddress);
                messageSubscriber.startRecv();
            }

        private:
            void establishConnection(const std::string &pushAddress,
                                     const std::string &subscribeAddress)
            {
                sender.connect(pushAddress);
                messageSubscriber.connect(subscribeAddress);
            }

            TypesPack::ProgramInternals internals;
            TypesPack::View view;
            TypesPack::Controller controller;
            TypesPack::SocketInputPropagator inputPropagator;

            SignalsHandler &signalsHandler;
            MessageHandler messageHandler;

            Subscriber messageSubscriber;

            Common::Communication::SenderChannel sender;
            Common::Communication::SubscriberChannel subscriber;
        };
    }
}