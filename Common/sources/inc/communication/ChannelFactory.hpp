#pragma once

#include "communication/OneWayChannel.hpp"

#include <zmq/zmq.hpp>

#include <utility>

namespace Common
{
    namespace Communication
    {
        class ChannelFactory
        {
        public:
            template <typename Channel>
            static auto create()
            {
                return Channel{ std::ref(ctx) };
            }

            template <typename Channel>
            static auto createSubscriber(const std::string &subscribeString)
            {
                return Channel{ std::ref(ctx), subscribeString };
            }

        private:
            static zmq::context_t ctx;
        };
    }
}
