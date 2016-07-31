#pragma once

#include <zmq/zmq.hpp>

#include <type_traits>

#include <utils/traits/traits.hpp>

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

            using Puller = Type<zmq::socket_type::pull>;
            using Pusher = Type<zmq::socket_type::push>;
            using Subscriber = Type<zmq::socket_type::sub>;
        };

        template <typename Type,
                  typename = std::enable_if_t<utils::traits::is_any_of_v<Type,
                                                                         ChannelType::Puller,
                                                                         ChannelType::Pusher,
                                                                         ChannelType::Subscriber>>>
                  /*typename = std::enable_if_t<std::is_same_v <Type, ChannelType::Puller> ||
                                              std::is_same_v <Type, ChannelType::Pusher> ||
                                              std::is_same_v <Type, ChannelType::Subscriber>>>*/
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

        template <typename Type>
        class ReceiverChannel : public OneWayChannel<Type>
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

        class SenderChannel : public OneWayChannel<ChannelType::Pusher>
        {
        public:
            SenderChannel(zmq::context_t &context) :
                OneWayChannel<ChannelType::Pusher>(context)
            {}

            auto send(const std::string &str)
            {
                return m_socket.send(std::begin(str), std::end(str));
            }

            auto send(zmq::message_t &message)
            {
                return m_socket.send(message);
            }
        };

        class SubscriberChannel : public ReceiverChannel<ChannelType::Subscriber>
        {
        public:
            SubscriberChannel(zmq::context_t &context, const std::string &subscribeStr) :
                ReceiverChannel<ChannelType::Subscriber>(context)
            {
                m_socket.setsockopt(ZMQ_SUBSCRIBE, subscribeStr.c_str(), 0);
            }
        };
    }
}