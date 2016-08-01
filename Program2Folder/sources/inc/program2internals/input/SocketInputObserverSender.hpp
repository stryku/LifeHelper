#pragma once

#include <program2internals/input/InputObserver.h>

#include <communication/OneWayChannel.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>

#include <stdint.h>
#include <vector>

namespace P2
{
    namespace Input
    {
        class SocketInputObserverSender : public P2::Input::InputHandler
        {
        private:
            using Sender = Common::Communication::SenderChannel;

        public:
            SocketInputObserverSender(Sender &sender) :
                m_sender(sender)
            {}

            void decrementSum()
            {
                using Elem = utils::MessageBuild::Xml::Element<std::string>;

                utils::MessageBuild::Xml::Builder builder;

                builder.addElement(Elem{ "msg.type", "decrementSum" });

                m_sender.send(builder.build());
            }

        private:
            Sender &m_sender;
        };
    }
}
