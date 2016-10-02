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
              typename ModelObserver>
    class Instance
    {
    public:
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;

        Instance(Instance &&other) = default;
        Instance& operator=(Instance &&other) = default;

    private:
        friend class ProgramInternalsCreators::Creator;

        Instance() = default;

        std::shared_ptr<ModelObserver> modelObserver;
        std::shared_ptr<Model> model;
        std::shared_ptr<View> view;
        std::shared_ptr<InputPropagator> inputPropagator;
        std::shared_ptr<InputHandler> inputHandler;
    };
}