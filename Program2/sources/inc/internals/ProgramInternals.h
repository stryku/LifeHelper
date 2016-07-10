#ifndef PROGRAMINTERNALS_H
#define PROGRAMINTERNALS_H

#include <internals/view/View.h>
#include <internals/controller/Controller.h>
#include <internals/model/Model.h>
#include <internals/input/Input.h>

#include <vector>

class ProgramInternals
{
public:
    ProgramInternals( P2::Model::Model *model ) :
        m_model( model )
    {}

    void setModel( P2::Model::Model *model)
    {
        m_model = model;
    }

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
    P2::Model::Model *m_model;
};

#endif // PROGRAMINTERNALS_H
