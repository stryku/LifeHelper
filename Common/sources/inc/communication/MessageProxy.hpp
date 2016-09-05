#pragma once

namespace Common
{
    namespace Communication
    {
        template <typename Handler, typename MessageReceiver>
        class MessagesProxy
        {
        public:
            MessageProxy(Handler &&handler, MessageReceiver &&receiver) :
                receiver{ receiver },
                handler{ std::move(handler) }
            {}

            void start()
            {
                while (true) //todo make interruptable
                {
                    auto msg = receiver.recv();
                    handler.handle(std::move(msg));
                }
            }

        private:

            MessageReceiver receiver;
            Handler handler;
        }
    }
}