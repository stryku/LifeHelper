#ifndef PROGRAMINTERNALS_H
#define PROGRAMINTERNALS_H

#include <program2internals/view/View.h>
#include <program2internals/controller/Controller.h>
#include <program2internals/model/Model.h>
#include <program2internals/input/Input.h>

#include <vector>

namespace P2
{
    class ProgramInternals
    {
    public:
        ProgramInternals(P2::Controller::Controller *controller) :
            controller{ controller }
        {}

        void addView(P2::View::View *view)
        {
            controller->registerView(view);
        }

        void addInputPropagator(P2::Input::InputPropagator *input)
        {
            inputs.push_back(input);
            input->setInputHandler(controller);
        }

        void setController(P2::Controller::Controller *neCcontroller)
        {
            controller = neCcontroller;
        }

    private:
        std::vector < P2::Input::InputPropagator* > inputs;
        P2::Controller::Controller *controller;
    };
}
#endif // PROGRAMINTERNALS_H
