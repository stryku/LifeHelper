#pragma once

#include "Communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"
#include "utils/ToString.hpp"

namespace P2
{
    namespace View
    {
        template <typename Sender>
        class SocketView
        {
        public:
            SocketView(Sender &&sender) :
                sender{ std::move(sender) }
            {}

            SocketView(SocketView&&) = default;
            SocketView& operator=(SocketView&&) = default;

            SocketView(const SocketView&) = delete;
            SocketView& operator=(const SocketView&) = delete;

            void updateSum(size_t newSum)
            {
                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                const std::vector<Elem> elements
                {
                    Elem{ "msg.type", "updateSum" },
                    Elem{ "msg.internals", utils::toString(newSum) }
                };

                builder.addElements(elements);

                sender.send(builder.build());
            }

        private:
            Sender sender;
        };
    }
}