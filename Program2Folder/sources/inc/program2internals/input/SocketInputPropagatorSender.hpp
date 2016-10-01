#pragma once

#include "program2internals/input/InputObserver.hpp"

#include "communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"

#include <stdint.h>
#include <vector>
#include <functional>

namespace P2
{
    namespace Input
    {
        template <typename Sender>
        class SocketInputPropagatorSender
        {
        public:
            template <typename Factory>
            SocketInputPropagatorSender() :
                sender{ Factory::createSenderForInputHandler() }
            {}

            SocketInputPropagatorSender(Sender &&sender) :
                sender{ std::move(sender) }
            {}

            SocketInputPropagatorSender(SocketInputPropagatorSender &&other) = default;
            SocketInputPropagatorSender& operator=(SocketInputPropagatorSender &&other) = default;

            SocketInputPropagatorSender(const SocketInputPropagatorSender &) = delete;
            SocketInputPropagatorSender& operator=(const SocketInputPropagatorSender &) = delete;

            void connect(const std::string &address)
            {
                sender.connect(address);
            }

            void decrementSum()
            {
                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                builder.addElement(Elem{ "msg.type", "decrementSum" });

                sender.send(builder.build());
            }

        private:
            Sender sender;
        };
    }
}
