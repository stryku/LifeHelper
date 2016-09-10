#pragma once

#include <utility>

namespace God
{
    namespace Communication
    {
        template <typename Sub,
                  typename Pub,
                  typename AddressProvider,
                  typename FrontendBackendBinder>
        class Proxy
        {
        public:
            Proxy(Sub &&subscriber,
                  Pub &&publisher) :
                subscriber{ std::move(subscriber) },
                publisher{ std::move(publisher) }
            {}

            Proxy(Proxy&&) = default;
            Proxy& operator=(Proxy&&) = default;

            Proxy() = delete;
            Proxy(const Proxy&) = delete;
            Proxy& operator=(const Proxy&) = delete;

            void startBindings()
            {
                subscriber.bind(AddressProvider::subscriberAddress);
                publisher.bind(AddressProvider::publisherAddress);
                FrontendBackendBinder::bind(subscriber, publisher);
            }

            constexpr auto subscriberAddress()
            {
                return AddressProvider::subscriberAddress;
            }

            constexpr auto publisherAddress()
            {
                return AddressProvider::publisherAddress;
            }

        private:
            Sub subscriber;
            Pub publisher;
        };
    }
}