#pragma once

#include "utils/log.hpp"

#include <string>

namespace P2
{
    namespace Communication
    {
        class MessageHandler
        {
        public:
            void handle(const std::string &msg)
            {
                LOG_FILE("MessageHandler::handle\n" << msg);
            }
        };
    }
}