#pragma once 

#include <zmq.h>

namespace Common
{
    class Publisher
    {
        Publisher()
        {
            sock = zmq_socket( nullptr, 0 );
        }

        void *sock;
    };
}