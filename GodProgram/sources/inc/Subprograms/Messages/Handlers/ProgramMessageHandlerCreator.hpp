#pragma once

#include "Subprograms/Messages/Handlers/MessageHandler.hpp"

namespace God
{
    namespace Subprograms
    {
        class SignalHandler;

        namespace Messages
        {
            namespace Handlers
            {
                class Creator
                {
                public:
                    template <typename ConcreteHandler>
                    static ConcreteHandler create(SignalHandler &signalHandler,
                                                  ConcreteHandler::ControllerType &controller)
                    {
                        return { std::ref(signalHandler),
                                 std::ref(controller) };
                    }
                };
            }
        }
    }
}