#pragma once

#include <Subprograms/SubprogramSignalHandler.hpp>

#include <functional>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Handlers
            {
                template <typename ConcreteHandler,
                          typename Parser>
                class MessageHandler
                {
                public:
                    MessageHandler() = default;

                    MessageHandler(SignalsHandler &signalHandler) /*:
                        signalHandler{ signalHandler }*/
                    {}

                    MessageHandler(MessageHandler &&other) /*:
                        signalHandler{ std::move(other.signalHandler) }*/
                    {}

                    MessageHandler& operator=(MessageHandler &&other)
                    {
                        //signalHandler = std::move(other.signalHandler);
                        return *this;
                    }


                    void handle(const std::string &strMsg)
                    {
                        auto parsed = Parser::parse(strMsg);

                        if (parsed.type == Messages::MessageType::MODEL_SIGNAL)
                        {
                            auto signalType = parsed.internalMessage.getType<SignalType>();
                            //signalHandler.get().signal(signalType, "");
                        }
                        else
                        {
                            //static_cast<ConcreteHandler*>(this)->handle_impl(parsed);
                        }
                    }

                private:
                    std::reference_wrapper<SignalsHandler> *signalHandler;
                };
            }
        }
    }
}