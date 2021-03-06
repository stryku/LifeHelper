#pragma once

#include "Subprograms/Messages/Parsers/Program2MessageParser.hpp"
#include "Subprograms/Messages/Handlers/MessageHandler.hpp"
#include "Subprograms/SubprogramSignalHandler.hpp"

#include "Communication/ChannelFactory.hpp"
#include "Communication/OneWayChannel.hpp"

#include "program2internals/model/SocketModelReceiver.hpp"
#include "program2internals/ProgramInfo.hpp"

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
                    using Model = P2::Info::TypesPack::ModelReceiver;

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
                        auto internals = parsed.internalMessage;

                        auto type = internals.getType<Program2Message::SubprogramMsgType>();
                        switch (type)
                        {
                            case Program2Message::SubprogramMsgType::UPDATE_SUM:
                                updateSum(parsed);
                            default:
                                break;
                        }
                    }

                private:
                    void updateSum(const Program2Message &parsed)
                    {
                        if (auto ptr = model.lock())
                            ptr->newSumValue(parsed.internalMessage.get<size_t>());
                    }

                    std::weak_ptr<Model> model;
                };
            }
        }
    }
}