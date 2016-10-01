#pragma once

#include "utils/log.hpp"

#include <utility>
#include <thread>

namespace God
{
    namespace Communication
    {
        template <typename Sub,
                  typename Pub,
                  typename AddressProvider,
                  typename FrontendBackendBinder,
                  typename Capturer = void>
        class Proxy
        {
        public:
            Proxy(Sub &&subscriber,
                  Pub &&publisher,
                  Capturer *capturer = nullptr)
                : subscriber{ std::move(subscriber) }
                , publisher{ std::move(publisher) }
                , capturer{capturer}
            {}

            Proxy(Proxy&&) = default;
            Proxy& operator=(Proxy&&) = default;

            Proxy() = delete;
            Proxy(const Proxy&) = delete;
            Proxy& operator=(const Proxy&) = delete;

            void startBindings()
            {
                LOG_FILE("Proxy::startBindings subscriber: " << AddressProvider::subscriberAddress);
                subscriber.bind(AddressProvider::subscriberAddress);

                LOG_FILE("Proxy::startBindings publisher: " << AddressProvider::publisherAddress);
                publisher.bind(AddressProvider::publisherAddress);
                auto bindFunction = [this] 
                {
                    FrontendBackendBinder::bind(subscriber, publisher, capturer); 
                };

                thread = std::thread{ bindFunction };
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
            std::thread thread;
            Capturer *capturer;
        };
    }
}