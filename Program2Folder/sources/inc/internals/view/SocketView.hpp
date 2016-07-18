#pragma once

#include "View.h"

#include <utils/message_builders/XmlMessageBuilder.hpp>
#include <communication/CommunicationChannel.hpp>
#include <utils/ToString.hpp>

namespace P2
{
    namespace View
    {
        class SocketView : public View
        {
            using Sender = Common::Communication::SenderChannel;

        public:
            SocketView(Sender &sender) :
                m_sender(sender)
            {}

            virtual void updateSum(size_t newSum) override
            {
                using Elem = utils::MessageBuild::Xml::Element<std::string>;

                utils::MessageBuild::Xml::Builder builder;

                const std::vector<Elem> elements
                {
                    Elem{"msg.type", "updateSum"},
                    Elem{"msg.value", utils::toString(newSum)}
                };

                builder.addElements(elements);

                m_sender.send(builder.build());
            }

        private:
            Sender &m_sender;
        };
    }
}