#pragma once

#include "Subprograms/Messages/Parsers/MessageParser.hpp"
#include "Subprograms/Messages/SubprogramMessage.hpp"


#include <string>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Parsers
            {
                class Program2 : public MessageParser<Program2, Program2Message>
                {
                private:
                    using MessageType = P2::Communication::MessageType::ToGod::Type;

                public:
                    Messages::Program2Message parse_internal(boost::property_tree::ptree &tree,
                                                             Program2Message &msg) const noexcept 
                    {
                        msg.internalMessage.setType<Program2Message::SubprogramMsgType>(parseType(tree));
                        msg.internalMessage.set<size_t>(parseValue(tree));
                        return msg;
                    }

                private:
                    Program2Message::SubprogramMsgType parseType(boost::property_tree::ptree &tree) const noexcept
                    {
                        auto strType = tree.get<std::string>("msg.internal.type");
                        return P2::Communication::MessageType::ToGod::fromString(strType);
                    }

                    size_t parseValue(boost::property_tree::ptree &tree) const noexcept
                    {
                        auto strValue = tree.get<std::string>("msg.internal.value.new_sum");
                        
                        try
                        {
                            return static_cast<size_t>(std::stoul(strValue));
                        }
                        catch (std::invalid_argument &e)
                        {
                            LOG("Program2Parser::parseValue invalid argument: " << strValue);
                        }
                        catch (std::out_of_range &e)
                        {
                            LOG("Program2Parser::parseValue argument out of range: " << strValue);
                        }

                        return 0;
                    }
                    
                };
            }
        }
    }
}