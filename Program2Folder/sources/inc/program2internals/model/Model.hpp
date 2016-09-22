#ifndef P2MODEL_H
#define P2MODEL_H

#include "utils/log.hpp"
#include "program2internals/model/ModelObserver.hpp"

#include <vector>
#include <memory>

namespace P2
{
    namespace Model
    {
        template <typename ModelObserver>
        class Model
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

                for(auto &modelObserver : modelObservers)
                    if(auto ptr = modelObserver.lock())
                        ptr->newSumValue( sum );
            }

            void registerObserver(std::weak_ptr<ModelObserver> observer )
            {
                LOG_FILE("Model::registerObserver");
                modelObservers.push_back( observer );
            }

        private:
            size_t sum = 0;
            std::vector<std::weak_ptr<ModelObserver>> modelObservers;
        };
    }
}
#endif // P2MODEL_H
