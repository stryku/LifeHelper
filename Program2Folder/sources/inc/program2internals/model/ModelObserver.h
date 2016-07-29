#ifndef P2MODELOBSERVER_H
#define P2MODELOBSERVER_H


#include <stdint.h>
namespace P2
{
    namespace Model
    {
        class ModelObserver
        {
        public:
            virtual ~ModelObserver() {}

            virtual void newSumValue( size_t newSum ) = 0;
        };
    }
}

#endif // P2MODELOBSERVER_H
