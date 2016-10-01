#pragma once

#include "program2internals/communication/MessageType.hpp"

namespace P2
{
    namespace Communication
    {
        struct MessageFromGod
        {
            MessageType::FromGod::Type type;
        };
    }
}