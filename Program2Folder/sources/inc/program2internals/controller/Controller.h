#ifndef P2CONTROLLER_H
#define P2CONTROLLER_H

#include <program2internals/input/InputHandler.h>
#include <program2internals/model/ModelObserver.h>
#include <program2internals/input/InputObserver.h>
#include <program2internals/view/View.h>

#include <vector>

namespace P2
{
    namespace Controller
    {
        class Controller : public P2::Input::InputHandler, public P2::Model::ModelObserver
        {
        public:
            Controller() {}

            void decrementSum()
            {
                inputObserver->decrementSum();
            }

            void setInputObserver( P2::Input::InputObserver *observer )
            {
                inputObserver = observer;
            }

            void registerView( P2::View::View *view )
            {
                views.push_back( view );
            }

            void newSumValue( size_t newSum )
            {
                for( auto &view : views )
                    view->updateSum( newSum );
            }

        private:
            P2::Input::InputObserver* inputObserver;
            std::vector<P2::View::View*> views;
        };
    }
}
#endif // P2CONTROLLER_H
