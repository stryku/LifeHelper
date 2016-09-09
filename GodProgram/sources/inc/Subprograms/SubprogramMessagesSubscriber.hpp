#pragma once

#include <communication/OneWayChannel.hpp>

#include <thread>
#include <functional>
#include <memory>

namespace God
{
    namespace Subprograms
    {
        template <typename MessageHandler, typename SocketFactory>
        class Subscriber
        {
        private:
            using SubChannel = Common::Communication::SubscriberChannel;

        public:
            Subscriber(const std::string &subscribeStr,
                       std::weak_ptr<MessageHandler> msgHandler) noexcept :
                subscriberChannel{ SocketFactory::createSubscriber<SubChannel>(subscribeStr) },
                msgHandler{ msgHandler }
            {}

            Subscriber(Subscriber &&other) noexcept = default;
            Subscriber& operator=(Subscriber &&other) noexcept = default;

            Subscriber() = delete;
            Subscriber(const Subscriber &) = delete;
            Subscriber& operator=(const Subscriber &) = delete;

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

                        if(auto ptr = msgHandler.lock())
                            ptr->handle(msg.str());
                    }
                };

                recvThread = std::thread{ loop };
            }

        private:
            SubChannel subscriberChannel;
            std::weak_ptr<MessageHandler> msgHandler;

            std::thread recvThread;

            bool interrupted{ false };
        };
    }
}