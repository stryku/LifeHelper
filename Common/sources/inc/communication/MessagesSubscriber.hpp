#pragma once

#include "utils/log.hpp"
#include "communication/OneWayChannel.hpp"

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
                LOG_FILE("Subscriber::connect( " << addr << " )");
                return subscriberChannel.connect(addr);
            }

            void interrupt()
            {
                LOG_FILE("Subscriber::interrupt");
                interrupted = true;
            }

            void startRecv()
            {
                LOG_FILE("Subscriber::startRecv");

                auto loop = [this]
                {
                    zmq::message_t msg;

                    while (!interrupted)
                    {
                        try
                        {
                            LOG_FILE("Subscriber receiving...");
                            auto ret = subscriberChannel.recvTimeout(msg); 

                            LOG_FILE("Subscriber received");

                            if (ret == EINTR)
                            {
                                LOG_FILE("Subscriber interrupted");
                                break;
                            }

                            if (auto ptr = msgHandler.lock())
                            {
                                LOG_FILE("Subscriber passing message to handle");
                                ptr->handle(eraseSubscriptionString(msg.str()));
                            }
                            else
                                LOG_FILE("Subscriber msgHandler expired");
                        }
                        catch (const zmq::error_t& ex)
                        {
                            LOG_FILE("Subscriber catched zmq::error_t: " << ex.what());
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
                LOG_FILE("Subscriber::stop");

                interrupt();
                if (recvThread.joinable())
                    recvThread.join();

                LOG_FILE("Subscriber::stopped");
            }

        private:
            std::string eraseSubscriptionString(const std::string &oryginalMsg)
            {
                auto pos = oryginalMsg.find(' ');
                return oryginalMsg.substr(pos);
            }

            SubChannel subscriberChannel;
            std::weak_ptr<MessageHandler> msgHandler;

            std::thread recvThread;

            bool interrupted{ false };
        };
    }
}