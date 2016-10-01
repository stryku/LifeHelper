#pragma once

#include <string>
#include <functional>

namespace Common
{
    namespace Communication
    {
        template <typename Receiver, typename ReceiverFactory>
        class ProxyCapturer
        {
            using Callback = std::function<void(const std::string&)>;
        public:
            ProxyCapturer(Callback receivedCallback)
                : receiver{ ReceiverFactory::create<Receiver>() }
                , callback{ receivedCallback }
            {}

            void start(const std::string &address)
            {
                LOG_FILE("ProxyCapturer connecting: " << address);
                receiver.connect(address);

                auto loop = [this]
                {
                    zmq::message_t msg;

                    while (!interrupted)
                    {
                        try
                        {
                            LOG_FILE("ProxyCapturer receiving...");
                            auto ret = receiver.recvTimeout(msg);

                            LOG_FILE("ProxyCapturer received");

                            if (ret == EINTR)
                            {
                                LOG_FILE("ProxyCapturer interrupted");
                                break;
                            }

                            LOG_FILE("ProxyCapturer passing message to callback");
                            callback(msg.str());
                        }
                        catch (const zmq::error_t& ex)
                        {
                            LOG_FILE("ProxyCapturer catched zmq::error_t: " << ex.what());
                            if (ex.num() != ETERM)
                                throw;
                        }
                    }
                };

                recvThread = std::thread{ loop };
            }

            void stop()
            {
                LOG_FILE("ProxyCapturer::stop");

                interrupt();
                if (recvThread.joinable())
                    recvThread.join();

                LOG_FILE("ProxyCapturer::stopped");
            }

            void interrupt()
            {
                LOG_FILE("Subscriber::interrupt");
                interrupted = true;
            }

        private:
            Receiver receiver;
            Callback callback;
            std::thread recvThread;

            bool interrupted{ false };

        };
    }
}