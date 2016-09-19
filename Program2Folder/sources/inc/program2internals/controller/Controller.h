#ifndef P2CONTROLLER_H
#define P2CONTROLLER_H

#include <program2internals/input/InputHandler.h>
#include <program2internals/model/ModelObserver.h>
#include <program2internals/input/InputObserver.h>
#include <program2internals/view/View.h>

#include <vector>
#include <memory>

namespace P2
{
    namespace Controller
    {
        template <typename InputObserver, typename View>
        class Controller : public P2::Input::InputHandler, public P2::Model::ModelObserver
        {
        public:
            void decrementSum()
            {
                LOG_FILE("Controller::decrementSum");

                if (auto ptr = inputObserver.lock())
                    ptr->decrementSum();
            }

            void setInputObserver( std::weak_ptr<InputObserver> observer )
            {
                LOG_FILE("Controller::setInputObserver");

                inputObserver = observer;
            }

            void registerView(std::weak_ptr<View> view)
            {
                LOG_FILE("Controller::registerView");

                views.push_back( view );
            }

            void newSumValue( size_t newSum )
            {
                LOG_FILE("Controller::newSumValue");

                for( auto &weakView : views )
                    if(auto view = weakView.lock())
                        view->updateSum( newSum );
            }

        private:
            std::weak_ptr<InputObserver> inputObserver;
            std::vector<std::weak_ptr<View>> views;
        };
    }
}
#endif // P2CONTROLLER_H
