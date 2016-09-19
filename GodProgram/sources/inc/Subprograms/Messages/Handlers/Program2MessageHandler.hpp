#pragma once

#include "Subprograms/Messages/Parsers/Program2MessageParser.hpp"
#include "Subprograms/Messages/Handlers/MessageHandler.hpp"
#include "Subprograms/SubprogramSignalHandler.hpp"

#include "Communication/ChannelFactory.hpp"
#include "Communication/OneWayChannel.hpp"

#include "program2internals/controller/Controller.h"
#include "program2internals/model/SocketModel.hpp"

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
                    using Model = P2::Model::SocketModel<ControllerType, 
                                                         Common::Communication::PublisherChannel,
                                                         Common::Communication::ChannelFactory>;

                    Program2() = default;
                    Program2(std::weak_ptr<SignalsHandler> handler, std::weak_ptr<Model> model) noexcept :
                        MessageHandler{ handler },
                        model{ model }
                    {}

                    Program2(Program2 &&) = default;
                    Program2& operator=(Program2 &&) = default;

                    Program2(const Program2&) = delete;
                    Program2& operator=(const Program2&) = delete;

                    void handle_impl(const Program2Message &parsed)
                    {
                    }

                private:
                    std::weak_ptr<Model> model;
                };
            }
        }
    }
}