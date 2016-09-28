#pragma once

#include <communication/OneWayChannel.hpp>

#include <thread>
#include <functional>
#include <memory>

namespace Common
{
    namespace Communication
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
                        try
                        {
                            auto ret = subscriberChannel.recvTimeout(msg, 500);

                            if (ret == EINTR)//todo add logs
                                break;

                            if (auto ptr = msgHandler.lock())
                                ptr->handle(msg.str());
                        }
                        catch (const zmq::error_t& ex)
                        {
                            // recv() throws ETERM when the zmq context is destroyed,
                            //  as when AsyncZmqListener::Stop() is called
                            if (ex.num() != ETERM)
                                throw;
                        }
                    }
                };

                recvThread = std::thread{ loop };
            }

            void stop()
            {
                interrupt();
                if (recvThread.joinable())
                    recvThread.join();
            }

        private:
            SubChannel subscriberChannel;
            std::weak_ptr<MessageHandler> msgHandler;

            std::thread recvThread;

            bool interrupted{ false };
        };
    }
}