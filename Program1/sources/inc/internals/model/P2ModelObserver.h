#ifndef P2MODELOBSERVER_H
#define P2MODELOBSERVER_H


#include <stdint.h>

class P2ModelObserver
{
public:
    P2ModelObserver();
    virtual ~P2ModelObserver() {}

    virtual void newSumValue(size_t newSum) = 0;
};

#endif // P2MODELOBSERVER_H
