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
        template <typename TypesPack, typename MessageHandler>
        class Instance 
        {
        public:
            Instance(QTabWidget &tabWidget,
                     zmq::context_t &context,
                     const std::string &pushAddress,
                     const std::string &subscribeAddress,
                     const std::string &subscribeStr,
                     SignalsHandler &signalsHandler) :
                internals{ &controller },
                view{ &tabWidget },
                socketInputOvserverSender{ sender },
                messageHandler{ signalsHandler, controller },
                messageSubscriber{ context, subscribeStr, messageHandler },
                sender{ context }
            {
                inputPropagator.setInputHandler(&socketInputOvserverSender);
                internals.addView(&view);
                internals.addInputPropagator(&inputPropagator);

                establishConnection(pushAddress, subscribeAddress);
                messageSubscriber.startRecv();
            }

            Instance(const Instance&) = delete;
            Instance& operator=(const Instance&) = delete;

            Instance(Instance&&) = default;
            Instance& operator=(Instance&&) = default;

        private:
            void establishConnection(const std::string &pushAddress,
                                     const std::string &subscribeAddress)
            {
                sender.connect(pushAddress);
                messageSubscriber.connect(subscribeAddress);
            }

            typename TypesPack::ProgramInternals internals;
            typename TypesPack::View view;
            typename TypesPack::Controller controller;
            typename TypesPack::InputPropagator inputPropagator;
            typename TypesPack::SocketInputObserverSender socketInputOvserverSender;

            MessageHandler messageHandler;

            Subscriber<MessageHandler> messageSubscriber;

            Common::Communication::SenderChannel sender;
        };
    }
}