#pragma once

#include <string>
#include <stdexcept>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace MessageType
            {
                enum class Type
                {
                    MODEL_CHANGE,
                    MODEL_SIGNAL
                };

                std::string toString(Type type)
                {
                    switch (type)
                    {
                    case God::Subprograms::Messages::MessageType::Type::MODEL_CHANGE: return "MODEL_CHANGE";
                    case God::Subprograms::Messages::MessageType::Type::MODEL_SIGNAL: return "MODEL_SIGNAL";

                    default:
                        throw std::invalid_argument("SignalType::toString(<invalid type>)");
                    }
                }

                Type fromString(const std::string &str)
                {
                    if (str == "MODEL_CHANGE") return Type::MODEL_CHANGE;
                    if (str == "MODEL_SIGNAL") return Type::MODEL_SIGNAL;

                    throw std::invalid_argument("SignalType::fromString(" + str + ")");
                }
            }
        }
    }
}