#pragma once

#include "program2internals/input/InputObserver.h"

#include "communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"

#include <vector>

namespace P2
{
    namespace Input
    {
        class SocketInputPropagatorReceiver : public P2::Input::InputObserver
        {
        private:
            using Receiver = Common::Communication::SubscriberChannel;

        public:
            SocketInputPropagatorReceiver(Receiver &receiver) :
                m_receiver(receiver)
            {}

            void decrementSum()
            {
                m_inputObserver->decrementSum();
            }

            void addInputObserver(InputObserver *observer)
            {
                m_inputObserver = observer;
            }

        private:
            Receiver &m_receiver;
            InputObserver *m_inputObserver;
        };
    }
}
