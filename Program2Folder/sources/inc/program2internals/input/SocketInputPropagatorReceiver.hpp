#pragma once

#include "utils/log.hpp"

#include "communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"

#include <vector>
#include <memory>

namespace P2
{
    namespace Input
    {
        template <typename Receiver, typename InputObserver>
        class SocketInputPropagatorReceiver
        {
        public:
            SocketInputPropagatorReceiver(Receiver &&receiver) :
                receiver{ std::move(receiver) }
            {}

            void decrementSum()
            {
                LOG("SocketInputPropagatorReceiver::decrementSum");

                if (auto ptr = inputObserver.lock())
                    ptr->decrementSum();
                else
                    LOG("SocketInputPropagatorReceiver::decrementSum inputObserver ptr expired");
            }

            void addInputObserver(std::weak_ptr<InputObserver> observer)
            {
                inputObserver = observer;
            }

        private:
            Receiver receiver;
            std::weak_ptr<InputObserver> inputObserver;
        };
    }
}
