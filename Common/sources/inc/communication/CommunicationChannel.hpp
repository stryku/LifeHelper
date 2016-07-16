#pragma once

#include "OneWayChannel.hpp"

namespace Common
{
    namespace Communication
    {
        class CommunicationChannel
        {
        public:
            CommunicationChannel(zmq::context_t &context);
            CommunicationChannel(CommunicationChannel &&other);
            CommunicationChannel& operator=(CommunicationChannel &&other) noexcept;
            CommunicationChannel(const CommunicationChannel&) = delete;
            CommunicationChannel& operator=(const CommunicationChannel&) = delete;

            auto recv(zmq::message_t &message);
            auto send(zmq::message_t &message);
            auto bind(const std::string &addr);
            auto connect(const std::string &addr);

        private:
            OneWayChannel<ChannelType::Receiver> m_receiver;
            OneWayChannel<ChannelType::Sender> m_sender;
        };
    }
}