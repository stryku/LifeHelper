#pragma once

#include <Subprograms/SubprogramSignalHandler.hpp>

#include <functional>
#include <memory>

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
                    MessageHandler(std::weak_ptr<SignalsHandler> signalHandler) :
                        signalHandler{ signalHandler }
                    {}

                    MessageHandler(MessageHandler &&other) = default;
                    MessageHandler& operator=(MessageHandler &&other) = default;

                    void handle(const std::string &strMsg)
                    {
                        auto parsed = Parser::parse(strMsg);

                        if (parsed.type == Messages::MessageType::MODEL_SIGNAL)
                        {
                            auto signalType = parsed.internalMessage.getType<SignalType>();
                            if(auto ptr = signalHandler.lock())
                                ptr->signal(signalType, "");
                        }
                        else
                        {
                            if (auto ptr = signalHandler.lock())
                                static_cast<ConcreteHandler*>(this)->handle_impl(parsed);
                        }
                    }

                private:
                    std::weak_ptr<SignalsHandler> signalHandler;
                };
            }
        }
    }
}