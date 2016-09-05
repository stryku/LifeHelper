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
        class SocketInputObserverSender : public P2::Input::InputHandler
        {
        private:
            using Sender = Common::Communication::SenderChannel;

        public:
            SocketInputObserverSender() = delete;
            SocketInputObserverSender(Sender &sender) :
                senderRef(sender)
            {}

            SocketInputObserverSender(SocketInputObserverSender &&other) :
                senderRef(std::move(other.senderRef))
            {}

            SocketInputObserverSender& operator=(SocketInputObserverSender &&other)
            {
                senderRef = std::move(other.senderRef);
            }

            SocketInputObserverSender(const SocketInputObserverSender &) = delete;
            SocketInputObserverSender& operator=(const SocketInputObserverSender &) = delete;

            void decrementSum()
            {
                using Elem = utils::MessageBuild::Xml::Element<std::string>;

                utils::MessageBuild::Xml::Builder builder;

                builder.addElement(Elem{ "msg.type", "decrementSum" });

                senderRef.get().send(builder.build());
            }

        private:
            std::reference_wrapper<Sender> senderRef;
        };
    }
}
