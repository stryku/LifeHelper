#pragma once

#include "communication/OneWayChannel.hpp"

#include "Subprograms/SubprogramSignalHandler.hpp"
#include "Communication/MessagesSubscriber.hpp"
#include "Subprograms/Messages/Handlers/Program2MessageHandler.hpp"
#include "Subprograms/SubprogramSignalHandler.hpp"

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
            using Subscriber = Common::Communication::Subscriber<MessageHandler, SocketFactory>;

        public:
            Instance(QWidget *tabWidget,
                     const std::string &pushAddress,
                     const std::string &subscribeAddress,
                     const std::string &subscribeStr,
                     SignalsHandler &&signalsHandler) :
                modelSender{ std::make_shared<typename TypesPack::ModelSender>(subscribeStr) },
                inputHandler{ std::make_shared<typename TypesPack::InputHandler>(modelSender) },
                inputPropagator{ std::make_shared<typename TypesPack::InputPropagator>(inputHandler) },
                modelObserver{ std::make_shared<typename TypesPack::ModelObserver>() },
                modelReceiver{ std::make_shared<typename TypesPack::ModelReceiver>(modelObserver) },
                view{ std::make_shared<typename TypesPack::View>(tabWidget, "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui") },
                signalsHandler{ std::make_shared<SignalsHandler>(std::move(signalsHandler)) },
                messageHandler{ std::make_shared<MessageHandler>(this->signalsHandler, modelReceiver) },
                messageSubscriber{ std::make_unique<Subscriber>(subscribeStr, messageHandler) }
            {
                view->connectWithInput(*inputPropagator);
                modelObserver->registerView(view);

                establishConnection(pushAddress, subscribeAddress);
            }

            Instance(const Instance&) = delete;
            Instance& operator=(const Instance&) = delete;

            Instance(Instance &&other) = default;
            Instance& operator=(Instance &&other) = default;

        private:
            void establishConnection(const std::string &pushAddress,
                                     const std::string &subscribeAddress)
            {
                modelSender->connect(pushAddress);
                messageSubscriber->connect(subscribeAddress);
                messageSubscriber->startRecv();
            }

            std::shared_ptr<typename TypesPack::ModelSender> modelSender;
            std::shared_ptr<typename TypesPack::InputHandler> inputHandler;
            std::shared_ptr<typename TypesPack::InputPropagator> inputPropagator;
            std::shared_ptr<typename TypesPack::ModelObserver> modelObserver;
            std::shared_ptr<typename TypesPack::ModelReceiver> modelReceiver;
            std::shared_ptr<typename TypesPack::View> view;

            std::shared_ptr<SignalsHandler> signalsHandler;
            std::shared_ptr<MessageHandler> messageHandler;
            std::unique_ptr<Subscriber> messageSubscriber;
        };
    }
}