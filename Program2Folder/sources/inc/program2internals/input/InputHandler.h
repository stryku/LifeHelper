#ifndef P2INPUTHANDLER_H
#define P2INPUTHANDLER_H

namespace P2
{
    namespace Input
    {
        class InputHandler
        {
        public:
            virtual ~InputHandler() {}

            virtual void decrementSum() = 0;
        };
    }
}
#endif // P2INPUTHANDLER_H
