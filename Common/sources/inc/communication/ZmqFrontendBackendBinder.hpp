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
                static void bind(Frontend &frontend, Backend &backend, void *capturer = nullptr)
                {
                    try
                    {
                        zmq::proxy(static_cast<void*>(frontend.getSocket()), static_cast<void*>(backend.getSocket()), capturer);
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