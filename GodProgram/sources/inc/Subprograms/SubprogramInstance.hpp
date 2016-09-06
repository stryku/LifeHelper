#pragma once

#include <communication/OneWayChannel.hpp>

#include <Subprograms/SubprogramSignalHandler.hpp>
#include <Subprograms/SubprogramMessagesSubscriber.hpp>
#include <Subprograms/Messages/Handlers/Program2MessageHandler.hpp>
#include "Subprograms/SubprogramSignalHandler.hpp"

#include <program2internals/input/SocketInputObserverSender.hpp>

#include <QTabWidget>

#include <memory>

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
                     SignalsHandler &&signalsHandler) :
                sender{ context },
                controller{ std::make_shared<TypesPack::Controller>() },
                internals{ controller },
                view{ std::make_shared<typename TypesPack::View>(&tabWidget, "programs/Program2/uiforms/Program2Form.ui") },
                socketInputOvserverSender{ std::make_shared<typename TypesPack::SocketInputObserverSender>(sender) },
                signalsHandler{ std::make_shared<SignalsHandler>(std::move(signalsHandler)) },
                messageHandler{ std::make_shared<MessageHandler>(this->signalsHandler, controller) },
                messageSubscriber{ context, subscribeStr, messageHandler }
            {
                /*inputPropagator.setInputHandler(&socketInputOvserverSender);
                internals.addView(&view);
                internals.addInputPropagator(&inputPropagator);

                establishConnection(pushAddress, subscribeAddress);*/
                //messageSubscriber.startRecv();
            }

            Instance(const Instance&) = delete;
            Instance& operator=(const Instance&) = delete;

            Instance(Instance &&other) = default;
            Instance& operator=(Instance &&other) = default;

        private:
            void establishConnection(const std::string &pushAddress,
                                     const std::string &subscribeAddress)
            {
                sender.connect(pushAddress);
                messageSubscriber.connect(pushAddress);
            }

            Common::Communication::SenderChannel sender;
            std::shared_ptr<typename TypesPack::Controller> controller;
            typename TypesPack::ProgramInternals internals;
            std::shared_ptr<typename TypesPack::View> view;
            std::shared_ptr<typename TypesPack::InputPropagator> inputPropagator;
            std::shared_ptr<typename TypesPack::SocketInputObserverSender> socketInputOvserverSender;

            std::shared_ptr<SignalsHandler> signalsHandler;
            std::shared_ptr<MessageHandler> messageHandler;
            Subscriber<MessageHandler> messageSubscriber;


        };
    }
}