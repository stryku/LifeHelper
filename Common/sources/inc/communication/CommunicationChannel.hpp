#pragma once

#include "OneWayChannel.hpp"

#include <string>

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

            auto& getSender()
            {
                return std::ref(m_sender);
            }

            auto& getReceiver()
            {
                return std::ref(m_receiver);
            }

        private:
            static constexpr auto getInprocAddress() noexcept
            {
                return "inproc://publisher";
            }

            static constexpr auto getIpcAddress() noexcept
            {
                return "tcp://127.0.0.1";
            }

            static constexpr auto getIpcPort() noexcept
            {
                return "1423";
            }

            void startProxy()
            {
                m_pubProxy.bind(getInprocAddress());
                m_receiver.bind("tcp://*:" + std::string( getIpcPort() ));
            }

            ReceiverChannel m_receiver;
            SenderChannel m_sender;

            zmq::socket_t m_pubProxy;
        };
    }
}