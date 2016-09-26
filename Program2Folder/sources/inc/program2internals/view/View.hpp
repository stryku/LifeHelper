#ifndef P2VIEW_H
#define P2VIEW_H

#include <stdint.h>

namespace P2
{
    namespace View
    {
        class View
        {
        public:
            virtual ~View() {}

            virtual void updateSum( size_t newSum1 ) = 0;
            //virtual void updateLabel(const QString &str) = 0;
        };
    }
}

#endif // P2VIEW_H
