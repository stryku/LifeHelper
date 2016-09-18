#pragma once

#include "Subprograms/Messages/MessageType.hpp"
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

                        msg.type = parseSignalType(tree);

                        if (msg.type == MesageType::Type::MODEL_SIGNAL)
                        {
                            msg.internalMessage.setType<SignalType::Type>(parseSignalType(tree));
                            return msg;
                        }
                        else
                            return static_cast<ConcreteParser*>(this)->parse_internal(msg);
                    }

                private:
                    MessageType::Type parseMessageType(boost::property_tree::ptree &tree) const
                    {
                        auto strType = tree.get<std::string>("msg.type");
                        return MesageType::fromString(strType);
                    }

                    SignalType::Type parseSignalType(boost::property_tree::ptree &tree) const
                    {
                        auto strType = tree.get<std::string>("msg.internal");
                        return SignalType::fromString(strType);
                    }
                };
            }
        }
    }
}