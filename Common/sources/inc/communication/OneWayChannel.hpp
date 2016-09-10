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
            using xSubscriber = Type<zmq::socket_type::xsub>;
            using Publisher = Type<zmq::socket_type::pub>;
            using xPublisher = Type<zmq::socket_type::xpub>;
        };

        template <typename Type,
                  typename = std::enable_if_t<utils::traits::is_any_of_v<Type,
                                                                         ChannelType::Puller,
                                                                         ChannelType::Pusher,
                                                                         ChannelType::Subscriber,
                                                                         ChannelType::xPublisher,
                                                                         ChannelType::Publisher,
                                                                         ChannelType::xSubscriber>>>
        class OneWayChannel
        {
        public:
            OneWayChannel(zmq::context_t &context) :
                m_context(context),
                m_socket(context, Type::socketType)
            {}
            OneWayChannel(OneWayChannel&&) noexcept = default;
            OneWayChannel& operator=(OneWayChannel&&) noexcept = default;

            auto bind(const std::string &addr)
            {
                return m_socket.bind(addr);
            }

            auto connect(const std::string &addr)
            {
                return m_socket.connect(addr);
            }

            auto &getSocket()
            {
                return m_socket;
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
            ReceiverChannel(ReceiverChannel&&) noexcept = default;
            ReceiverChannel& operator=(ReceiverChannel&&) noexcept = default;
            

            auto recv(zmq::message_t &message)
            {
                return m_socket.recv(&message);
            }
        };

        template <typename Sender>
        class SenderChannel : public OneWayChannel<Sender>
        {
        public:
            SenderChannel(zmq::context_t &context) :
                OneWayChannel<Sender>(context)
            {}
            SenderChannel(SenderChannel&&) noexcept = default;
            SenderChannel& operator=(SenderChannel&&) noexcept = default;

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

            SubscriberChannel(SubscriberChannel&&) noexcept = default;
            SubscriberChannel& operator=(SubscriberChannel&&) noexcept = default;
        };

        class xSubscriberChannel : public ReceiverChannel<ChannelType::xSubscriber>
        {
        public:
            xSubscriberChannel(zmq::context_t &context) :
                ReceiverChannel<ChannelType::xSubscriber>(context)
            {}

            xSubscriberChannel(xSubscriberChannel&&) noexcept = default;
            xSubscriberChannel& operator=(xSubscriberChannel&&) noexcept = default;
        };

        class PublisherChannel : public SenderChannel<ChannelType::Publisher>
        {
        public:
            PublisherChannel(zmq::context_t &context) :
                SenderChannel<ChannelType::Publisher>(context)
            {}

            PublisherChannel(PublisherChannel&&) noexcept = default;
            PublisherChannel& operator=(PublisherChannel&&) noexcept = default;
        };

        class xPublisherChannel : public OneWayChannel<ChannelType::xPublisher>
        {
        public:
            xPublisherChannel(zmq::context_t &context) :
                OneWayChannel<ChannelType::xPublisher>(context)
            {}

            xPublisherChannel(xPublisherChannel&&) noexcept = default;
            xPublisherChannel& operator=(xPublisherChannel&&) noexcept = default;
        };
    }
}