#pragma once

#include "ModelObserver.h"

#include <communication/OneWayChannel.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>
#include <utils/ToString.hpp>

#include <stdint.h>
namespace P2
{
    namespace Model
    {
        class SocketModelObserverSender : public ModelObserver
        {
        private:
            using Sender = Common::Communication::PublisherChannel;

        public:
            SocketModelObserverSender(Sender &sender) :
                m_sender(sender)
            {}

            virtual ~SocketModelObserverSender() {}

            virtual void newSumValue(size_t newSum) override
            {
                using Elem = utils::MessageBuild::Xml::Element<std::string>;

                utils::MessageBuild::Xml::Builder builder;

                const std::vector<Elem> elements
                {
                    Elem{ "msg.type", "updateSum" },
                    Elem{ "msg.value", utils::toString(newSum) }
                };

                builder.addElements(elements);

                m_sender.send(builder.build());
            }

        private:
            Sender &m_sender;
        };
    }
}
