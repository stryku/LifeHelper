#pragma once

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace SignalType
        {
            enum class Type
            {
                HEARTBEAT_SIGNAL,
                ERROR_SIGNAL,
                CLEAN_CLOSE_SIGNAL,
                UNDEF
            };

            constexpr const char* toString(Type type)
            {
                return (type == Type::CLEAN_CLOSE_SIGNAL) ? "CLEAN_CLOSE_SIGNAL" :
                    (type == Type::ERROR_SIGNAL) ? "ERROR_SIGNAL" :
                    (type == Type::HEARTBEAT_SIGNAL) ? "HEARTBEAT_SIGNAL" :
                    "UNDEF";
            }

            Type fromString(const std::string &str)
            {
                if (str == "CLEAN_CLOSE_SIGNAL") return Type::CLEAN_CLOSE_SIGNAL;
                if (str == "ERROR_SIGNAL") return Type::ERROR_SIGNAL;
                if (str == "CLEAN_CLOSE_SIGNAL") return Type::CLEAN_CLOSE_SIGNAL;

                return Type::UNDEF;
            }
        }
    }
}