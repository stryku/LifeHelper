#ifndef P2INPUT_H
#define P2INPUT_H

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
                if(auto ptr = inputHandler.lock())
                    ptr->decrementSum();
            }

            void setInputHandler( std::weak_ptr<InputHandler> handler )
            {
                inputHandler = handler;
            }

            auto createDecrementSumCallback()
            {
                auto callback = [this] { notifyDecrementSum(); };
                return callback;
            }

        private:
            std::weak_ptr<InputHandler> inputHandler;
        };
    }
}
#endif // P2INPUT_H
