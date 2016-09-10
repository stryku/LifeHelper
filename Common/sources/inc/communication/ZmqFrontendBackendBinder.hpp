#pragma once

#include "utils/log.hpp"

#include <zmq/zmq.hpp>

namespace God
{
    namespace Communication
    {
        namespace detail
        {
            class ZmqFrontendBackendBinder
            {
            public:
                template <typename Frontend, typename Backend>
                static void bind(Frontend &frontend, Backend &backend)
                {
                    try
                    {
                        zmq_proxy(&frontend.getSocket(), &backend.getSocket(), nullptr);
                    }
                    catch (zmq::error_t &e)
                    {
                        LOG(e.what());
                    }
                }
            };
        }
    }
}