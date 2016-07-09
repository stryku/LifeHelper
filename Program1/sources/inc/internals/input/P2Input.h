#ifndef P2INPUT_H
#define P2INPUT_H

#include "P2InputHandler.h"

class P2InputPropagator
{
public:
    P2InputPropagator() {}

    void notifyDecrementSum()
    {
        m_inputHandler->decrementSum();
    }

    void setInputHandler(P2InputHandler *handler)
    {
        m_inputHandler = handler;
    }

    auto createDecrementSumCallback()
    {
        auto callback = [this]{notifyDecrementSum();};
        return callback;
    }

private:
    P2InputHandler *m_inputHandler;
};

#endif // P2INPUT_H
