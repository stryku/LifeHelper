#pragma once

#include <string>
#include <stdexcept>

namespace P2
{
    namespace Communication
    {
        namespace MessageType
        {
            enum class Type
            {
                UPDATE_SUM
            };

            std::string toString(Type type)
            {
                switch (type)
                {
                case Type::UPDATE_SUM: return "UPDATE_SUM";

                default:
                    throw std::invalid_argument("MessageType::toString(<invalid argument>)");
                }
            }

            Type fromString(const std::string &str)
            {
                if (str == "UPDATE_SUM") return Type::UPDATE_SUM;

                throw std::invalid_argument("MessageType::toString( " + str + " )");
            }
        }
    }
}