#pragma once

#include "utils/log.hpp"

#include <memory>

namespace P2
{
    namespace Model
    {
        template <typename ModelObserver>
        class SocketModelReceiver
        {
        public:
            SocketModelReceiver(std::weak_ptr<ModelObserver> modelObserver)
                : modelObserver{ modelObserver }
            {}

            void newSumValue(size_t sum)
            {
                LOG_FILE("SocketModelReceiver::newSumValue( "<<sum<<" )");

                if (auto ptr = modelObserver.lock())
                    ptr->newSumValue(sum);
                else
                    LOG_FILE("SocketModelReceiver::modelObserver expired");
            }

        private:
            std::weak_ptr<ModelObserver> modelObserver;
        };
    }
}