#pragma once

#include "Subprograms/Messages/Parsers/Program2MessageParser.hpp"
#include "Subprograms/Messages/Handlers/MessageHandler.hpp"
#include "Subprograms/SubprogramSignalHandler.hpp"

#include "program2internals/controller/Controller.h"

#include <string>
#include <memory>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Handlers
            {
                class Program2 : public MessageHandler<Program2, Parsers::Program2>
                {
                public:
                    using ControllerType = P2::Info::TypesPack::Controller;

                    Program2() = default;
                    Program2(std::weak_ptr<SignalsHandler> handler, std::weak_ptr<ControllerType> controller) noexcept :
                        MessageHandler{ handler },
                        controller{ controller }
                    {}

                    Program2(Program2 &&) = default;
                    Program2& operator=(Program2 &&) = default;

                    Program2(const Program2&) = delete;
                    Program2& operator=(const Program2&) = delete;

                    void handle_impl(const Program2Message &parsed)
                    {
                    }

                private:
                    std::weak_ptr<ControllerType> controller;
                };
            }
        }
    }
}