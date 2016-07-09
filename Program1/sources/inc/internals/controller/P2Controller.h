#ifndef P2CONTROLLER_H
#define P2CONTROLLER_H

#include <internals/input/P2InputHandler.h>
#include <internals/model/P2ModelObserver.h>
#include <internals/input/P2InputObserver.h>
#include <internals/view/P2View.h>

#include <vector>

class P2Controller : public P2InputHandler, public P2ModelObserver
{
public:
    P2Controller() {}

    void decrementSum()
    {
        inputObserver->decrementSum();
    }

    void setInputObserver(P2InputObserver *observer)
    {
        inputObserver = observer;
    }

    void registerView(P2View *view)
    {
        views.push_back(view);
    }

    void newSumValue(size_t newSum)
    {
        for(auto &view : views)
            view->updateSum(newSum);
    }

private:
    P2InputObserver* inputObserver;
    std::vector<P2View*> views;
};

#endif // P2CONTROLLER_H
