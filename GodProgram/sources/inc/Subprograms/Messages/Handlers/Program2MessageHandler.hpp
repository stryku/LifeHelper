#pragma once

#include <Subprograms/Messages/Parsers/Program2MessageParser.hpp>
#include <Subprograms/Messages/Handlers/MessageHandler.hpp>

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Handlers
            {
                class Program2 : public MessageHandler<Program2, Parsers::Program2>
                {
                public:
                    void handle_impl(const Program2Message &parsed)
                    {

                    }
                };
            }
        }
    }
}