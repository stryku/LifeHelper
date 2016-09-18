#pragma once

#include "Subprograms/Messages/Parsers/MessageParser.hpp"
#include "Subprograms/Messages/SubprogramMessage.hpp"

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Parsers
            {
                class Program2 : MessageParser<Program2, Program2Message>
                {
                public:
                    Messages::Program2Message parse_internal(Program2Message &msg) noexcept
                    {
                        return msg;
                    }
                };
            }
        }
    }
}