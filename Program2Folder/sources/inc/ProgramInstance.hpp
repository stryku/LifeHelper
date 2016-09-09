#pragma once

#include <memory>

namespace P2
{
    template <typename Controller,
              typename View,
              typename InputPropagator,
              typename InputObserver,
              typename Internals,
              typename ParentPlaceholder>
    class Instance
    {
    public:
        Instance(ParentPlaceholder *parent) :
            controller{ std::make_shared<Controller>() },
            internals{ controller },
            view{ std::make_shared<View>(parent, "uiforms/Program2Form.ui") },
            inputPropagator{ std::make_shared<InputPropagator>() },
            inputObserver{ std::make_shared<InputObserver>() }
        {
            view->connectWithInput(inputPropagator.get());
            inputObserver->registerObserver(controller.get());
            controller->registerView(view);
            controller->setInputObserver(inputObserver);

            //internals.setController(controller);
            internals.addInputPropagator(inputPropagator);
            internals.addView(view);
        }

        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        Instance(Instance &&other) = default;
        Instance& operator=(Instance &&other) = default;

    private:
        std::shared_ptr<Controller> controller;
        ProgramInternals internals;
        std::shared_ptr<View> view;
        std::shared_ptr<InputPropagator> inputPropagator;
        std::shared_ptr<InputObserver> inputObserver;
    };
}