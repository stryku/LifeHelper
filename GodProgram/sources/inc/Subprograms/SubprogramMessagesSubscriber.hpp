#pragma once

#include <communication/OneWayChannel.hpp>

#include <thread>
#include <functional>

namespace God
{
    namespace Subprograms
    {
        template <typename MessageHandler>
        class Subscriber
        {
        public:
            Subscriber(zmq::context_t &context,
                       const std::string &subscribeStr,
                       MessageHandler &msgHandler) noexcept :
                subscriberChannel{ context, subscribeStr },
                msgHandler{ msgHandler }
            {}

            Subscriber(Subscriber &&other) noexcept :
                subscriberChannel{ std::move(other.subscriberChannel) },
                msgHandler{ std::move(other.msgHandler) },
                recvThread{ std::move(other.recvThread) },
                interrupted{ other.interrupted }
            {}

            Subscriber& operator=(Subscriber &&other) noexcept
            {
                subscriberChannel = std::move(other.subscriberChannel);
                msgHandler = std::move(other.msgHandler);
                recvThread = std::move(other.recvThread);
                interrupted = other.interrupted;

                return *this;
            }

            Subscriber() = delete;
            Subscriber(Subscriber &) = delete;
            Subscriber& operator=(Subscriber &) = delete;

            auto connect(const std::string &addr)
            {
                return subscriberChannel.connect(addr);
            }

            void interrupt()
            {
                interrupted = true;
            }

            void startRecv()
            {
                auto loop = [this]
                {
                    zmq::message_t msg;

                    while (!interrupted)
                    {
                        auto ret = subscriberChannel.recv(msg);

                        if (ret == EINTR)//todo add logs
                            break;

                        msgHandler.handle(msg.str());
                    }
                };

                recvThread = std::thread{ loop };
            }

        private:
            Common::Communication::SubscriberChannel subscriberChannel;
            std::reference_wrapper<MessageHandler> msgHandler;

            std::thread recvThread;

            bool interrupted{ false };
        };
    }
}