#pragma once

#include "OneWayChannel.hpp"

namespace Common
{
    namespace Communication
    {
        class CommunicationChannel
        {
        public:
            CommunicationChannel(zmq::context_t &context) :
                m_receiver(context),
                m_sender(context)
            {}

            CommunicationChannel(CommunicationChannel &&other) :
                m_receiver(std::move(other.m_receiver)),
                m_sender(std::move(m_sender))
            {}

            CommunicationChannel& operator=(CommunicationChannel &&other) noexcept
            {
                m_receiver = std::move(other.m_receiver);
                m_sender = std::move(other.m_sender);
                return *this;
            }

            CommunicationChannel(const CommunicationChannel&) = delete;
            CommunicationChannel& operator=(const CommunicationChannel&) = delete;

            auto recv(zmq::message_t &message)
            {
                return m_receiver.recv(message);
            }

            auto send(const zmq::message_t &message)
            {
                return m_sender.send(message);
            }

            auto bind(const std::string &addr)
            {
                return m_receiver.bind(addr);
            }

            auto connect(const std::string &addr)
            {
                return m_receiver.connect(addr);
            }

        private:
            OneWayChannel<ChannelType::Receiver> m_receiver;
            OneWayChannel<ChannelType::Sender> m_sender;
        };
    }
}