#pragma once

#include "utils/log.hpp"
#include "program2internals/communication/MessageFromGod.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <sstream>

namespace P2
{
    namespace Communication
    {
        class MessageParser
        {
        public:
            static MessageFromGod parse(const std::string &strMsg)
            {
                std::istringstream iss(strMsg);
                boost::property_tree::ptree tree;
                boost::property_tree::read_xml(iss, tree);
                MessageFromGod msg;

                LOG_FILE("P2::MessageParser parsing:\n" << strMsg);

                msg.type = parseMessageType(tree);

                return msg;
            }

        private:
            static P2::Communication::MessageType::FromGod::Type parseMessageType(boost::property_tree::ptree &tree)
            {
                auto strType = tree.get<std::string>("msg.type");
                return P2::Communication::MessageType::FromGod::fromString(strType);
            }
        };
    }
}