#pragma once

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
                    void handle(const std::string &strMsg)
                    {
                        static_cast<ConcreteHandler*>(this)->handle_impl(Parser::parse(strMsg));
                    }
                };
            }
        }
    }
}