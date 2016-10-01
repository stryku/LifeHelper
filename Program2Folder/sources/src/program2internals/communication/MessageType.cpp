#include "program2internals/communication/MessageType.hpp"

namespace P2
{
    namespace Communication
    {
        namespace MessageType
        {
            namespace ToGod
            {
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

            namespace FromGod
            {
                std::string toString(Type type)
                {
                    switch (type)
                    {
                    case Type::DECREMT_SUM: return "DECREMT_SUM";

                    default:
                        throw std::invalid_argument("MessageType::toString(<invalid argument>)");
                    }
                }

                Type fromString(const std::string &str)
                {
                    if (str == "DECREMT_SUM") return Type::DECREMT_SUM;

                    throw std::invalid_argument("MessageType::toString( " + str + " )");
                }
            }
        }
    }
}