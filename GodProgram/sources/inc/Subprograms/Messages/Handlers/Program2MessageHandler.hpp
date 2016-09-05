#pragma once

#include <Subprograms/Messages/Parsers/Program2MessageParser.hpp>
#include <Subprograms/Messages/Handlers/MessageHandler.hpp>
#include <Subprograms/SubprogramSignalHandler.hpp>

#include <program2internals/controller/Controller.h>

#include <string>

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
                    Program2() = default;
                    Program2(SignalsHandler &handler, P2::Controller::Controller &controller) noexcept :
                        MessageHandler{ handler }/*,
                        controller{ controller }*/
                    {}

                    Program2(Program2 && other) noexcept :
                        MessageHandler{ std::move(other) }/*,
                        controller{ std::move(other.controller) }*/
                    {}

                    Program2(Program2 && other, SignalsHandler &handler) noexcept :
                        MessageHandler{ handler }/*,
                        controller{ std::move(other.controller) }*/
                    {}

                    Program2& operator=(Program2 && other) noexcept
                    {
                        //controller = std::move(other.controller);
                        return *this;
                    }

                    Program2(const Program2&) = delete;
                    Program2& operator=(const Program2&) = delete;

                    void handle_impl(const Program2Message &parsed)
                    {
                    }

                private:
                    std::reference_wrapper<P2::Controller::Controller> *controller;
                };
            }
        }
    }
}