#pragma once

#include <string>
#include <stdexcept>

namespace P2
{
    namespace Communication
    {
        namespace MessageType
        {
            namespace ToGod
            {
                enum class Type
                {
                    UPDATE_SUM
                };

                std::string toString(Type type);

                Type fromString(const std::string &str);
            }

            namespace FromGod
            {
                enum class Type
                {
                    DECREMT_SUM
                };

                std::string toString(Type type);

                Type fromString(const std::string &str);
            }
        }
    }
}