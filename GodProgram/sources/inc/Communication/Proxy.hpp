#pragma once

#include <utility>

namespace God
{
    namespace Communication
    {
        template <typename Socket,
                  typename AddressProvider,
                  typename FrontendBackendBinder>
        class Proxy
        {
        public:
            MainProxy(Socket &&subscriber,
                      Socket &&publisher) :
                subscriber{ std::move(subscriber) },
                publisher{ std::move(publisher) }
            {}

            MainProxy(MainProxy&&) = default;
            MainProxy& operator=(MainProxy&&) = default;

            MainProxy() = delete;
            MainProxy(const MainProxy&) = delete;
            MainProxy& operator=(const MainProxy&) = delete;

            void startBindings()
            {
                subscriber.bind(AddressProvider::subscribeAddress);
                publisher.bind(AddressProvider::publisherAddress);
                FrontendBackendBinder::bind(publisher, subscriber);
            }

            constexpr auto subscriberAddress()
            {
                return AddressProvider::subscribeAddress;
            }

            constexpr auto publisherAddress()
            {
                return AddressProvider::publisherAddress;
            }

        private:
            Socket subscriber;
            Socket publisher;
        };
    }
}