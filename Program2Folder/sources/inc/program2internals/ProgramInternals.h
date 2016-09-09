#ifndef PROGRAMINTERNALS_H
#define PROGRAMINTERNALS_H

#include <program2internals/view/View.h>
#include <program2internals/controller/Controller.h>
#include <program2internals/model/Model.h>
#include <program2internals/input/Input.h>

#include <vector>
#include <memory>

namespace P2
{
    template <typename Controller>
    class ProgramInternals
    {
    public:
        ProgramInternals(std::weak_ptr<Controller> controller) :
            controller{ controller }
        {}

        ProgramInternals(ProgramInternals&&) = default;
        ProgramInternals& operator=(ProgramInternals&&) = default;

        void addView(std::weak_ptr<P2::View::View> view)
        {
            if(auto ptr = controller.lock())
                ptr->registerView(view);
        }

        void addInputPropagator(std::weak_ptr<P2::Input::InputPropagator> input)
        {
            inputs.push_back(input);

            if (auto ptr = input.lock())
                if(auto controllerPtr = controller.lock())
                    ptr->setInputHandler(controllerPtr);
        }

    private:
        std::vector<std::weak_ptr<P2::Input::InputPropagator>> inputs;
        std::weak_ptr<Controller> controller;
    };
}
#endif // PROGRAMINTERNALS_H
