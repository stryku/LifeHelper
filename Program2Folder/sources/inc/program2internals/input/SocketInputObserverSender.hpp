#pragma once

#include <program2internals/input/InputObserver.h>

#include <communication/OneWayChannel.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>

#include <stdint.h>
#include <vector>
#include <functional>

namespace P2
{
    namespace Input
    {
        template <typename Sender>
        class SocketInputObserverSender : public P2::Input::InputHandler
        {
        public:
            template <typename Factory>
            SocketInputObserverSender() :
                sender{ Factory::createSenderForInputHandler() }
            {}

            SocketInputObserverSender(Sender &&sender) :
                sender{ std::move(sender) }
            {}

            SocketInputObserverSender(SocketInputObserverSender &&other) = default;
            SocketInputObserverSender& operator=(SocketInputObserverSender &&other) = default;

            SocketInputObserverSender(const SocketInputObserverSender &) = delete;
            SocketInputObserverSender& operator=(const SocketInputObserverSender &) = delete;

            void connect(const std::string &address)
            {
                sender.connect(address);
            }

            void decrementSum()
            {
                using Elem = utils::MessageBuild::Xml::Element<std::string>;

                utils::MessageBuild::Xml::Builder builder;

                builder.addElement(Elem{ "msg.type", "decrementSum" });

                sender.send(builder.build());
            }

        private:
            Sender sender;
        };
    }
}
