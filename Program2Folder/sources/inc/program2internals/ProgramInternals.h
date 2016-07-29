#ifndef PROGRAMINTERNALS_H
#define PROGRAMINTERNALS_H

#include <program2internals/view/View.h>
#include <program2internals/controller/Controller.h>
#include <program2internals/model/Model.h>
#include <program2internals/input/Input.h>

#include <vector>

class ProgramInternals
{
public:
    ProgramInternals()
    {}

    void addView(P2::View::View *view)
    {
        m_controller->registerView(view);
    }

    void addInput(P2::Input::InputPropagator *input)
    {
        inputs.push_back(input);
        input->setInputHandler(m_controller);
    }

    void setController(P2::Controller::Controller *controller)
    {
        m_controller = controller;
    }

private:
    std::vector < P2::Input::InputPropagator* > inputs;
    P2::Controller::Controller *m_controller;
};

#endif // PROGRAMINTERNALS_H
