#pragma once

#include "Communication/messages/XmlMessageBuilder.hpp"
#include "program2internals/communication/MessageType.hpp"

#include <memory>
#include <vector>

namespace P2
{
    namespace Model
    {
        template <typename Sender, typename SenderFactory>
        class SocketModelSender
        {
        public:
            SocketModelSender(const std::string &publishString)
                : sender{ SenderFactory::create<Sender>() }
                , publishString{ publishString }
            {}

            SocketModelSender(SocketModelSender&&) = default;
            SocketModelSender& operator=(SocketModelSender&&) = default;

            SocketModelSender(const SocketModelSender&) = delete;
            SocketModelSender& operator=(const SocketModelSender&) = delete;

            void connect(const std::string &address)
            {
                sender.connect(address);
            }

            void decrementSum()
            {
                LOG_FILE("Model::decrementSum");

                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                auto type = Communication::MessageType::FromGod::toString(Communication::MessageType::FromGod::Type::DECREMT_SUM);

                builder.addElement(Elem{ "msg.type", type })
                       .addPublishString(publishString);

                sender.send(builder.build());
            }

            void notifySumChange(size_t sum)
            {
                LOG_FILE("Model::notifySumChange");

                for (auto &modelObserver : modelObservers)
                    if(auto ptr = modelObserver.lock())
                        ptr->newSumValue(sum);
            }

        private:
            Sender sender;
            std::string publishString;
        };
    }
}