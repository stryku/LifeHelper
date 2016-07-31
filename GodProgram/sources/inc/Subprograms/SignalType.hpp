#pragma once

#include <string>

namespace God
{
    namespace Subprograms
    {
        enum class SignalType
        {
            HEARTBEAT_SIGNAL,
            ERROR_SIGNAL,
            CLEAN_CLOSE_SIGNAL,
            UNDEF
        };

        constexpr const char* signalTypeToString(SignalType type)
        {
            return (type == SignalType::CLEAN_CLOSE_SIGNAL) ? "CLEAN_CLOSE_SIGNAL" :
                   (type == SignalType::ERROR_SIGNAL) ? "ERROR_SIGNAL" :
                   (type == SignalType::HEARTBEAT_SIGNAL) ? "CLEAN_CLOSE_SIGNAL" :
                   "UNDEF";
        }

        SignalType signalTypeFromString(const std::string &str)
        {
            if (str == "CLEAN_CLOSE_SIGNAL") return SignalType::CLEAN_CLOSE_SIGNAL;
            if (str == "ERROR_SIGNAL") return SignalType::ERROR_SIGNAL;
            if (str == "CLEAN_CLOSE_SIGNAL") return SignalType::CLEAN_CLOSE_SIGNAL;

            return SignalType::UNDEF;
        }
    }
}