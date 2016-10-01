#pragma once

#include "ModelObserver.hpp"

#include "Communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"
#include "utils/ToString.hpp"

#include <stdint.h>

namespace P2
{
    namespace Model
    {
        class SocketModelObserverSender
        {
        private:
            using Sender = Common::Communication::PublisherChannel;

        public:
            SocketModelObserverSender(Sender &sender) :
                m_sender(sender)
            {}

            void newSumValue(size_t newSum)
            {
                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                const std::vector<Elem> elements
                {
                    Elem{ "msg.type", "updateSum" },
                    Elem{ "msg.internals", utils::toString(newSum) }
                };

                builder.addElements(elements);

                m_sender.send(builder.build());
            }

        private:
            Sender &m_sender;
        };
    }
}
