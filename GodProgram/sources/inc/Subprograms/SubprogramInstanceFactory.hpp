#pragma once

#include <Subprograms/helpers.hpp>
#include <Subprograms/SubprogramInstance.hpp>

#include <program2internals/ProgramInternals.h>
#include <program2internals/view/QtView.h>

#include <QTabWidget>

namespace God
{
    namespace Subprograms
    {
        class InstanceFactory
        {
        public:
            template <typename ProgramInternals,
                      typename View,
                      typename Controller,
                      typename InputPropagator>
            Instance<ProgramInternals,
                     View,
                     Controller,
                     InputPropagator> 
                create(QTabWidget &tabWidget, Subprograms::ModelId modelId)
            {
                return{ tabWidget, modelId };

                //Instance<ProgramInternals> instance;
                //Controller controller;
                //View view(&tabWidget);

                //controller.registerView(&view);


            }

            /*Instance<P2::ProgramInternals> createProgram2(QTabWidget &tabWidget, Subprograms::ModelId modelId)
            {
                P2::ProgramInternals internals;
                P2::Controller::Controller controller;

                P2::View::QtView qtView(&tabWidget);

                controller.registerView()

                internals.
            }*/
        };
    }
}