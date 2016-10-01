#pragma once

#include <memory>

namespace ProgramInternalsCreators
{
    class Creator;
}


namespace P2
{
    template <typename View,
              typename InputPropagator,
              typename InputHandler,
              typename Model,
              typename ModelObserver
              //typename Internals,
              /*typename ParentPlaceholder*/>
    class Instance
    {
        friend class ProgramInternalsCreators::Creator;

    public:
        //Instance(ParentPlaceholder *parent) :
        //    //internals{ controller },
        //    view{ std::make_shared<View>(parent, "C:/moje/programowanie/LifeController/bin/programs/Program2/uiforms/Program2Form.ui") },
        //    inputPropagator{ std::make_shared<InputPropagator>() },
        //    modelObserver { std::make_shared<ModelObserver>() },
        //    model{ std::make_shared<Model>() },
        //    inputHandler { std::make_shared<InputHandler>(model) }
        //{
        //    view->connectWithInput(*inputPropagator);
        //    model->registerObserver(modelObserver);
        //    modelObserver->registerView(view);
        //    inputPropagator->setInputHandler(inputHandler);
        //    //inputHandler->setInputObserver(model);

        //    //internals.setController(controller);
        //    //internals.addInputPropagator(inputPropagator);
        //    //internals.addView(view);
        //}

        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        Instance(Instance &&other) = default;
        Instance& operator=(Instance &&other) = default;

    private:
        Instance() = default;

        //ProgramInternals<Controller> internals;
        std::shared_ptr<ModelObserver> modelObserver;
        std::shared_ptr<Model> model;
        std::shared_ptr<View> view;
        std::shared_ptr<InputPropagator> inputPropagator;
        std::shared_ptr<InputHandler> inputHandler;
    };
}