#pragma once

#include <Subprograms/MessageParsers/Program2MessageParser.hpp>

#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace MessageHandlers
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

            class Program2 : public MessageHandler<Program2, MessageParsers::Program2>
            {
            public:
                void handle_impl(std::string parsed)
                {
                    
                }
            };
        }
    }
}