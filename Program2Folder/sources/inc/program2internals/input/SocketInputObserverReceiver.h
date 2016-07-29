#pragma once

#include <program2internals/input/InputObserver.h>

#include <communication/OneWayChannel.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>

#include <stdint.h>
#include <vector>

namespace P2
{
    namespace Input
    {
        class SocketInputObserverReceiver : public P2::Input::InputObserver
        {
        private:
            using Receiver = Common::Communication::ReceiverChannel;

        public:
            SocketInputObserverReceiver(Receiver &receiver) :
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
