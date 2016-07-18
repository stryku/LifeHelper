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
            CommunicationChannel(CommunicationChannel &&other) noexcept;
            CommunicationChannel& operator=(CommunicationChannel &&other) noexcept;
            CommunicationChannel(const CommunicationChannel&) = delete;
            CommunicationChannel& operator=(const CommunicationChannel&) = delete;

            auto recv();
            auto send(zmq::message_t &message);
            auto bind(const std::string &addr);
            auto connect(const std::string &addr);

        private:
            ReceiverChannel m_receiver;
            SenderChannel m_sender;
        };
    }
}