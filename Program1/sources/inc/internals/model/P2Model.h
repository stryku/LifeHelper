#ifndef P2MODEL_H
#define P2MODEL_H


#include <internals/input/P2InputObserver.h>
#include <internals/model/P2ModelObserver.h>

#include <stdint.h>
#include <vector>


class P2Model : public P2InputObserver
{
public:
    void decrementSum()
    {
        --sum;
        notifySumChange();
    }

    void notifySumChange()
    {
        for(auto &modelObserver : modelObservers)
            modelObserver->newSumValue(sum);
    }

    void registerObserver(P2ModelObserver *observer)
    {
        modelObservers.push_back(observer);
    }

private:
    size_t sum = 0;
    std::vector<P2ModelObserver*> modelObservers;

};
#endif // P2MODEL_H
