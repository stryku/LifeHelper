#pragma once

#include <Subprograms/SubprogramSignalHandler.hpp>

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
                    MessageHandler(SignalsHandler &signalHandler) :
                        signalHandler{ signalHandler }
                    {}

                    void handle(const std::string &strMsg)
                    {
                        auto parsed = Parser::parse(strMsg);

                        if (parsed.type == Messages::MessageType::MODEL_SIGNAL)
                        {
                            auto signalType = parsed.internalMessage.getType<SignalType>();
                            signalHandler.signal(signalType);
                        }
                        else
                        {
                            static_cast<ConcreteHandler*>(this)->handle_impl(parsed.internalMessage);
                        }
                    }

                private:
                    SignalsHandler &signalHandler;
                };
            }
        }
    }
}