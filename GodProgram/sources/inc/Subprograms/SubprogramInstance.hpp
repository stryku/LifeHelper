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
        template <typename TypesPack, typename MessageHandler, typename SocketFactory>
        class Instance 
        {
        private:
            using Publisher = Common::Communication::PublisherChannel;

        public:
            Instance(QWidget *tabWidget,
                     const std::string &pushAddress,
                     const std::string &subscribeAddress,
                     const std::string &subscribeStr,
                     SignalsHandler &&signalsHandler) :
                controller{ std::make_shared<TypesPack::Controller>() },
                internals{ controller },
                view{ std::make_shared<typename TypesPack::View>(tabWidget, "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui") },
                inputPropagator{ std::make_shared<typename TypesPack::InputPropagator>() },
                socketInputObserverSender{ std::make_shared<typename TypesPack::SocketInputObserverSender>(SocketFactory::create<Publisher>()) },
                signalsHandler{ std::make_shared<SignalsHandler>(std::move(signalsHandler)) },
                messageHandler{ std::make_shared<MessageHandler>(this->signalsHandler, controller) },
                messageSubscriber{ subscribeStr, messageHandler }
            {
                //establishConnection(pushAddress, subscribeAddress);
                //messageSubscriber.startRecv();

                view->connectWithInput(inputPropagator.get());
                inputPropagator->setInputHandler(controller);
                //inputObserver->registerObserver(controller.get());
                controller->registerView(view);
                controller->setInputObserver(socketInputObserverSender);

            }

            Instance(const Instance&) = delete;
            Instance& operator=(const Instance&) = delete;

            Instance(Instance &&other) = default;
            Instance& operator=(Instance &&other) = default;

        private:
            void establishConnection(const std::string &pushAddress,
                                     const std::string &subscribeAddress)
            {
                socketInputObserverSender->connect(pushAddress);
                messageSubscriber.connect(subscribeAddress);
            }

            //Common::Communication::PublisherChannel internalPublisher;
            std::shared_ptr<typename TypesPack::Controller> controller;
            typename TypesPack::ProgramInternals internals;
            std::shared_ptr<typename TypesPack::View> view;
            std::shared_ptr<typename TypesPack::InputPropagator> inputPropagator;
            std::shared_ptr<typename TypesPack::SocketInputObserverSender> socketInputObserverSender;

            std::shared_ptr<SignalsHandler> signalsHandler;
            std::shared_ptr<MessageHandler> messageHandler;
            Subscriber<MessageHandler, SocketFactory> messageSubscriber;
        };
    }
}