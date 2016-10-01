#pragma once

#include <Subprograms/helpers.hpp>
#include <Subprograms/SubprogramInstance.hpp>

//#include <program2internals/ProgramInternals.h>
#include <program2internals/view/QtView.hpp>

#include <QTabWidget>

#include <functional>

namespace God
{
    namespace Subprograms
    {
        class InstanceFactory
        {
        public:
            template <typename TypesPack, typename MessageHandler, typename InstanceType = Instance<TypesPack, MessageHandler>>
            static InstanceType create(QTabWidget &tabWidget,
                                                        zmq::context_t &context,
                                                        const std::string &pushAddress,
                                                        const std::string &subscribeAddress,
                                                        const std::string &subscribeStr,
                                                        SignalsHandler *signalHandler)
            {
                return InstanceType(tabWidget,
                                                      context,
                                                      pushAddress,
                                                      subscribeAddress,
                                                      subscribeStr,
                                                      *signalHandler);
            }
        };
    }
}