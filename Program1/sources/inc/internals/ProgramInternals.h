#ifndef PROGRAMINTERNALS_H
#define PROGRAMINTERNALS_H

#include <internals/view/P2View.h>
#include <internals/controller/P2Controller.h>
#include <internals/model/P2Model.h>
#include <internals/input/P2Input.h>

#include <vector>

class ProgramInternals
{
public:
    ProgramInternals(P2Model *model) :
        m_model(model)
    {}

    void setModel(P2Model *model)
    {
        m_model = model;
    }

    void addView(P2View *view)
    {
        m_controller->registerView(view);
    }

    void addInput(P2InputPropagator *input)
    {
        inputs.push_back(input);
        input->setInputHandler(m_controller);
    }

    void setController(P2Controller *controller)
    {
        m_controller = controller;
    }

private:
    std::vector<P2InputPropagator*> inputs;
    P2Controller *m_controller;
    P2Model *m_model;
};

#endif // PROGRAMINTERNALS_H
