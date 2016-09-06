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
        class Controller : public P2::Input::InputHandler, public P2::Model::ModelObserver
        {
        public:
            void decrementSum()
            {
                if (auto ptr = inputObserver.lock())
                    ptr->decrementSum();
            }

            void setInputObserver( std::weak_ptr<P2::Input::InputObserver> observer )
            {
                inputObserver = observer;
            }

            void registerView(std::weak_ptr<P2::View::View> view)
            {
                views.push_back( view );
            }

            void newSumValue( size_t newSum )
            {
                for( auto &weakView : views )
                    if(auto view = weakView.lock())
                        view->updateSum( newSum );
            }

        private:
            std::weak_ptr<P2::Input::InputObserver> inputObserver;
            std::vector<std::weak_ptr<P2::View::View>> views;
        };
    }
}
#endif // P2CONTROLLER_H
