#ifndef P2INPUTOBSERVER_H
#define P2INPUTOBSERVER_H



class P2InputObserver
{
public:
    virtual ~P2InputObserver() {}

    virtual void decrementSum() = 0;
};

#endif // P2INPUTOBSERVER_H
