#pragma once

namespace God
{
    namespace Communication
    {
        namespace detail
        {
            namespace AddressProvider
            {
                struct SubprogramToGod
                {
#ifdef WIN32
                    constexpr static auto subscriberAddress = "tcp://127.0.0.1:1555";
#else
                    constexpr static auto subscriberAddress = "ipc://127.0.0.1:1555";
#endif //WIN32
                    constexpr static auto publisherAddress = "inproc://internalPublisherBind:1555";
                };

                struct GodToSubprogram
                {
#ifdef WIN32
                    constexpr static auto publisherAddress = "tcp://127.0.0.1:1777";
#else
                    constexpr static auto publisherAddress = "ipc://127.0.0.1:1777";
#endif //WIN32
                    constexpr static auto subscriberAddress = "inproc://internalSubscriberBind:1777";
                };
            }
        }
    }
}