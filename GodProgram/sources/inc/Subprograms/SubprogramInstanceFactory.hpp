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
            }
        };
    }
}