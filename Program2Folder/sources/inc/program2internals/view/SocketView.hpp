#pragma once

#include "utils/log.hpp"

#include "Communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"
#include "utils/ToString.hpp"
#include "program2internals/communication/MessageType.hpp"

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

            void connect(const std::string &address)
            {
                LOG_FILE("SocketView::connect( " << address << " )");
                sender.connect(address);
            }

            void updateSum(size_t newSum)
            {
                LOG_FILE("SocketView::updateSum( " << newSum << " )");

                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                auto type = Communication::MessageType::ToGod::toString(Communication::MessageType::ToGod::Type::UPDATE_SUM);

                const std::vector<Elem> elements
                {
                    Elem{ "msg.type", "MODEL_CHANGE" },
                    Elem{ "msg.internal.type", type },
                    Elem{ "msg.internal.value.new_sum", utils::toString(newSum) }
                };

                builder.addElements(elements)
                       .addPublishString("1");

                auto msg = builder.build();

                LOG_FILE("SocketView::updateSum SENDING:\n" << msg);

                sender.send(msg);
            }

        private:
            Sender sender;
        };
    }
}

/*
<msg>
    <type>
        MODEL_CHANGE
    </type>
    <internal>
        <type>
            UPDATE_SUM
        </type>
        <value>
            <new_sum>
                sum value
            </new_sum>
        </value>
    </internal>
</msg>*/