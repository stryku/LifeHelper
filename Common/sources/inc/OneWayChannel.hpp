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
            static_assert(!std::is_same<Type, ChannelType::Receiver>::value &&
                          !std::is_same<Type, ChannelType::Sender>::value,
                          "OneWayChannel may be one of type ChannelType::Receiver or ChannelType::Sender only");

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

            template<typename std::enable_if<std::is_same<Type, ChannelType::Receiver>::value), int>::type = 0>
            void recv() 
            {}

            template<typename std::enable_if<std::is_same<Type, ChannelType::Sender>::value), int>::type = 0>
            void send()
            {}

            void bind()
            {}

            void connect()
            {}

        private:
            zmq::context_t &m_context;
            zmq::socket_t m_socket;
        };
    }
}