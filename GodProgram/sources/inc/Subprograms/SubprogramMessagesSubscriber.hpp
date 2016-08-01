#pragma once

#include <communication/OneWayChannel.hpp>

#include <thread>

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
            MessageHandler &msgHandler;

            std::thread recvThread;

            bool interrupted{ false };
        };
    }
}