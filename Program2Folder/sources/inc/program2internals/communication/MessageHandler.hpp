#pragma once

#include "utils/log.hpp"
#include "program2internals/communication/MessageType.hpp"

#include <string>
#include <memory>

namespace P2
{
    namespace Communication
    {
        template <typename Parser>
        class MessageHandler
        {
        public:
            template <typename InputPropagator>
            void connectWithInput(InputPropagator &inputPropagator)
            {
                notifyDecrementSumCallback = inputPropagator.createDecrementSumCallback();
            }

            void handle(const std::string &msg)
            {
                LOG_FILE("MessageHandler::handle\n" << msg);

                auto parsed = Parser::parse(msg);

                switch (parsed.type)
                {
                    case MessageType::FromGod::Type::DECREMT_SUM: 
                        notifyDecrementSumCallback();
                    break;

                    default:
                        LOG_FILE("MessageHandler::handle unreconized msg type");
                    break;
                }
            }

        private:
            std::function<void()> notifyDecrementSumCallback;
        };
    }
}