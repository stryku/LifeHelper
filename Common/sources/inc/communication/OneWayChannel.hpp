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

        template <typename Type>
        class OneWayChannel
        {
        public:
            static_assert(!std::is_same<Type, ChannelType::Receiver>::value &&
                          !std::is_same<Type, ChannelType::Sender>::value,
                          "OneWayChannel may be one of type ChannelType::Receiver or ChannelType::Sender only");

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

            auto recv(zmq::message_t &message)
            {
                static_assert(!std::is_same<Type, ChannelType::Receiver>::value, 
                              "Channel can recv only if its type is Receiver");

                return m_socket.recv(&message);
            }

            auto send(const zmq::message_t &message)
            {
                static_assert(!std::is_same<Type, ChannelType::Sender>::value, 
                              "Channel can send only if its type is Sender");

                return m_socket.send(message);
            }
            
            template<typename = std::enable_if<!std::is_same<Type, ChannelType::Sender>::value) >>
            auto send(const zmq::message_t &message)
            {
                return m_socket.send(message);
            }

            auto bind(const std::string &addr)
            {
                return m_socket.bind(addr);
            }

            auto connect(const std::string &addr)
            {
                return m_socket.connect(addr);
            }

        private:
            zmq::context_t &m_context;
            zmq::socket_t m_socket;
        };
    }
}