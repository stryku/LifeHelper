#pragma once

#include "Communication/messages/MessageType.hpp"
#include "Subprograms/Messages/SubprogramMessage.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <sstream>

namespace God
{
    namespace Subprograms
    {
        namespace Messages
        {
            namespace Parsers
            {
                template <typename ConcreteParser, typename Message>
                class MessageParser
                {
                public:
                    Message parse(const std::string &strMsg) const
                    {
                        std::istringstream iss(strMsg);
                        boost::property_tree::ptree tree;
                        boost::property_tree::read_xml(iss, tree);
                        Message msg;

                        msg.type = parseMessageType(tree);

                        if (msg.type == Common::Communication::Messages::MessageType::Type::MODEL_SIGNAL)
                        {
                            msg.internalMessage.setType<Common::Communication::SignalType::Type>(parseSignalType(tree));
                            return msg;
                        }
                        else
                            return static_cast<const ConcreteParser*>(this)->parse_internal(tree, msg);
                    }

                private:
                    Common::Communication::Messages::MessageType::Type parseMessageType(boost::property_tree::ptree &tree) const
                    {
                        auto strType = tree.get<std::string>("msg.type");
                        return Common::Communication::Messages::MessageType::fromString(strType);
                    }

                    Common::Communication::SignalType::Type parseSignalType(boost::property_tree::ptree &tree) const
                    {
                        auto strType = tree.get<std::string>("msg.internal");
                        return Common::Communication::SignalType::fromString(strType);
                    }
                };
            }
        }
    }
}