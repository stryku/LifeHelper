#pragma once

#include "utils/log.hpp"
#include "InputHandler.h"

#include <memory>

namespace P2
{
    namespace Input
    {
        class InputPropagator
        {
        public:
            void notifyDecrementSum()
            {
                LOG_FILE("InputPropagator::notifyDecrementSum");

                if(auto ptr = inputHandler.lock())
                    ptr->decrementSum();
                else
                    LOG_FILE("InputPropagator::notifyDecrementSum inputHandler ptr expired!");

            }

            void setInputHandler( std::weak_ptr<InputHandler> handler )
            {
                LOG_FILE("InputPropagator::setInputHandler");
                inputHandler = handler;
            }

            auto createDecrementSumCallback()
            {
                LOG_FILE("InputPropagator::createDecrementSumCallback");
                auto callback = [this] { notifyDecrementSum(); };
                return callback;
            }

        private:
            std::weak_ptr<InputHandler> inputHandler;
        };
    }
}
