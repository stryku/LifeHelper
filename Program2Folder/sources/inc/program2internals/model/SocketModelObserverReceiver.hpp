#pragma once

#include "ModelObserver.h"

#include "Communication/OneWayChannel.hpp"
#include "Communication/messages/XmlMessageBuilder.hpp"
#include "utils/ToString.hpp"

#include <stdint.h>
namespace P2
{
    namespace Model
    {
        class SocketModelObserverReceiver
        {
        public:
            void addModelObserver(ModelObserver *observer)
            {
                observers.push_back(observer);
            }

            void newSumValue(size_t newSum)
            {
                for (auto &observer : observers)
                    observer->newSumValue(newSum);
            }

        private:
            std::vector<ModelObserver*> observers;
        };
    }
}
