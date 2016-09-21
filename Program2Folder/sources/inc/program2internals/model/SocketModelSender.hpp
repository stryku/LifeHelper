#pragma once

#include "Communication/messages/XmlMessageBuilder.hpp"

#include <memory>
#include <vector>

namespace P2
{
    namespace Model
    {
        template <typename ModelObserver, typename Sender, typename SenderFactory>
        class SocketModel
        {
        public:
            SocketModel()
                : sender{ SenderFactory::create<Sender>() }
            {}

            void decrementSum()
            {
                LOG_FILE("Model::decrementSum");

                using Elem = Common::Communication::MessageBuilders::Xml::Element<std::string>;

                Common::Communication::MessageBuilders::Xml::Builder builder;

                builder.addElement(Elem{ "msg.type", "decrementSum" });

                sender.send(builder.build());
            }

            void notifySumChange(size_t sum)
            {
                LOG_FILE("Model::notifySumChange");

                for (auto &modelObserver : modelObservers)
                    if(auto ptr = modelObserver.lock())
                        ptr->newSumValue(sum);
            }

            void registerObserver(std::weak_ptr<ModelObserver> modelObserver)
            {
                LOG_FILE("Model::registerObserver()");

                modelObservers.push_back(observer);
            }

        private:
            std::vector<std::weak_ptr<ModelObserver>> modelObserver;
            Sender sender;
        };
    }
}