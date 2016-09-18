#ifndef P2MODEL_H
#define P2MODEL_H

#include "utils/log.hpp"
#include "program2internals/input/InputObserver.h"
#include "program2internals/model/ModelObserver.h"

#include <stdint.h>
#include <vector>

namespace P2
{
    namespace Model
    {
        class Model : public P2::Input::InputObserver
        {
        public:
            void decrementSum()
            {
                LOG_FILE("Model::decrementSum");
                --sum;
                notifySumChange();
            }

            void notifySumChange()
            {
                LOG_FILE("Model::notifySumChange");
                for( auto &modelObserver : modelObservers )
                    modelObserver->newSumValue( sum );
            }

            void registerObserver( ModelObserver *observer )
            {
                LOG_FILE("Model::registerObserver( " << std::hex << observer << ")");
                modelObservers.push_back( observer );
            }

        private:
            size_t sum = 0;
            std::vector<ModelObserver*> modelObservers;
        };
    }
}
#endif // P2MODEL_H
