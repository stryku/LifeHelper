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
            template <typename TypesPack>
            Instance<TypesPack> create(QTabWidget &tabWidget,
                                       ModelId modelId,
                                       const std::string &pushAddress,
                                       const std::string &subscribeAddress,
                                       const std::string &subscribeStr.
                                       SignalsHandler &signalHandler)
            {
                return { tabWidget,
                         modelId,
                         pushAddress,
                         subscribeAddress,
                         subscribeStr,
                         signalsHandler };
            }
        };
    }
}