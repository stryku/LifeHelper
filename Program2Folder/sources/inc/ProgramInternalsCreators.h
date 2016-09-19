#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

#include "program2internals/ProgramInternals.h"
#include "ProgramInstance.hpp"
#include "program2internals/view/QtView.h"
#include "program2internals/model/Model.h"
#include "program2internals/controller/Controller.h"
#include "program2internals/model/SocketModelObserverSender.hpp"
#include "program2internals/input/SocketInputPropagatorReceiver.h"

#include <QTabWidget>

namespace ProgramInternalsCreators
{
    class Creator
    {
        using LocalQtInstance = P2::Instance<
            P2::Controller::Controller<P2::Model::Model>,
            P2::View::QtView<P2::Input::InputPropagator>,
            P2::Input::InputPropagator,
            P2::Model::Model,
            P2::ProgramInternals<P2::Controller::Controller<P2::Model::Model>>,
            QWidget>;

        using RemoteInstance = P2::Instance<
            P2::Controller::Controller<P2::Model::Model>,
            P2::Model::SocketModelObserverSender,
            P2::Input::SocketInputPropagatorReceiver,
            P2::Model::Model,
            P2::ProgramInternals<P2::Controller::Controller<P2::Model::Model>>,
            void
        >;

    public:
        static LocalQtInstance createLocalQt(QWidget *qtViewWidgetParent);
        static RemoteInstance createRemote();
    };
    /*using RemoteInstance = P2::Instance<
        P2::Controller::Controller<P2::Model::Model>,
        P2::
    >;*/
}

#endif // PROGRAMFACTORY_H
