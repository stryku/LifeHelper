#pragma once

#include "communication/messages/MessageType.hpp"
#include "communication/messages/SignalType.hpp"
#include "utils/log.hpp"
#include "Subprograms/SubprogramSignalHandler.hpp"

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
                        LOG("God::MessageHandler::handle:\n" << strMsg);

                        auto parsed = Parser().parse(strMsg);

                        if (parsed.type == Common::Communication::Messages::MessageType::Type::MODEL_SIGNAL)
                        {
                            auto signalType = parsed.internalMessage.getType<Common::Communication::SignalType::Type>();
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