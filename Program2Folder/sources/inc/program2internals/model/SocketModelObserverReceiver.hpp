#pragma once

#include "ModelObserver.h"

#include <communication/OneWayChannel.hpp>
#include <utils/message_builders/XmlMessageBuilder.hpp>
#include <utils/ToString.hpp>

#include <stdint.h>
namespace P2
{
    namespace Model
    {
        class SocketModelChangesReceiver : public ModelObserver
        {
        private:
            using Receiver = Common::Communication::ReceiverChannel;

        public:
            SocketModelChangesReceiver(Receiver &receiver) :
                m_receiver(receiver)
            {}

            virtual ~SocketModelChangesReceiver() {}

            void addModelObserver(ModelObserver *observer)
            {
                observers.push_back(observer);
            }

            virtual void newSumValue(size_t newSum) override
            {
                for (auto &observer : observers)
                    observer->newSumValue(newSum);
            }

        private:
            Receiver &m_receiver;

            std::vector<ModelObserver*> observers;
        };
    }
}
