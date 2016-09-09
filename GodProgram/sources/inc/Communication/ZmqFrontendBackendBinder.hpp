#pragma once

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
                    zmq::proxy(&frontend, &backend, nullptr);
                }
            };
        }
    }
}