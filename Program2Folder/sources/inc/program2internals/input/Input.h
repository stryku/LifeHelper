#ifndef P2INPUT_H
#define P2INPUT_H

#include "InputHandler.h"
namespace P2
{
    namespace Input
    {
        class InputPropagator
        {
        public:
            InputPropagator() {}

            void notifyDecrementSum()
            {
                m_inputHandler->decrementSum();
            }

            void setInputHandler( InputHandler *handler )
            {
                m_inputHandler = handler;
            }

            auto createDecrementSumCallback()
            {
                auto callback = [this] { notifyDecrementSum(); };
                return callback;
            }

        private:
            InputHandler *m_inputHandler;
        };
    }
}
#endif // P2INPUT_H
