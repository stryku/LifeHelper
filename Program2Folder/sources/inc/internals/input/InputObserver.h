#ifndef P2INPUTOBSERVER_H
#define P2INPUTOBSERVER_H

namespace P2
{
    namespace Input
    {
        class InputObserver
        {
        public:
            virtual ~InputObserver() {}

            virtual void decrementSum() = 0;
        };
    }
}

#endif // P2INPUTOBSERVER_H
