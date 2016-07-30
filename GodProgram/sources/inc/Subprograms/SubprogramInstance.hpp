#pragma once

#include <QTabWidget>

namespace God
{
    namespace Subprograms
    {
        template <typename ProgramInternals,
                  typename View,
                  typename Controller,
                  typename InputPropagator>
            class Instance
        {
        public:
            Instance(QTabWidget &tabWidget, ModelId modelId) :
                internals { &controller },
                view{ &tabWidget }, 
                modelId{ modelId }
            {
                internals.addView(&view);
                internals.addInputPropagator(&inputPropagator);
            }

            void addView(View *view)
            {
                internals.addView(view);
            }

            void addInputPropagator(InputPropagator *input)
            {
                internals.addInputPropagator(input);
            }

            void setController(Controller *controller)
            {
                internals.setController(controller);
            }

        private:
            ProgramInternals internals;
            View view;
            Controller controller;
            InputPropagator inputPropagator;

            ModelId modelId;
        };
    }
}