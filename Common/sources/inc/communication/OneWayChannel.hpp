#pragma once

#include <zmq/zmq.hpp>

#include <type_traits>

namespace Common
{
    namespace Communication
    {
        namespace ChannelType
        {
            template <zmq::socket_type SocketType>
            struct Type
            {
                static constexpr zmq::socket_type socketType = SocketType;
            };

            using Receiver = Type<zmq::socket_type::pull>;
            using Sender = Type<zmq::socket_type::push>;
        };

        template <typename Type,
                  typename = std::enable_if_t<std::is_same_v <Type, ChannelType::Receiver> ||
                                              std::is_same_v <Type, ChannelType::Sender>>>
        class OneWayChannel
        {
        public:
            OneWayChannel(zmq::context_t &context) :
                m_context(context),
                m_socket(context, Type::socketType)
            {}

            OneWayChannel(OneWayChannel &&other) :
                m_context(std::move(other.m_context)),
                m_socket(std::move(m_socket))
            {}

            OneWayChannel& operator=(OneWayChannel &&other) noexcept
            {
                m_context = std::move(other.m_context);
                m_socket = std::move(other.m_socket);
                return *this;
            }

            OneWayChannel(const OneWayChannel&) = delete;
            OneWayChannel& operator=(const OneWayChannel&) = delete;

            auto bind(const std::string &addr)
            {
                return m_socket.bind(addr);
            }

            auto connect(const std::string &addr)
            {
                return m_socket.connect(addr);
            }

        protected:
            zmq::context_t &m_context;
            zmq::socket_t m_socket;
        };

        class ReceiverChannel : public OneWayChannel<ChannelType::Receiver>
        {
        public:
            ReceiverChannel(zmq::context_t &context) :
                OneWayChannel(context)
            {}

            auto recv(zmq::message_t &message)
            {
                return m_socket.recv(&message);
            }
        };

        class SenderChannel : public OneWayChannel<ChannelType::Sender>
        {
        public:
            SenderChannel(zmq::context_t &context) :
                OneWayChannel<ChannelType::Sender>(context)
            {}

            auto send(zmq::message_t &message)
            {
                return m_socket.send(message);
            }
        };
    }
}