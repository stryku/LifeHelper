#include "communication/ChannelFactory.hpp"

namespace Common
{
    namespace Communication
    {
        zmq::context_t ChannelFactory::ctx{ 1 };
    }
}
