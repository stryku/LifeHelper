#pragma once

#include <Subprograms/Messages/SubprogramMessage.hpp>

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace MessageParsers
        {
            class Program2
            {
            public: 
                static Messages::Program2Message parse(const std::string &msg) noexcept
                {
                    return {};
                }
            };
        }
    }
}