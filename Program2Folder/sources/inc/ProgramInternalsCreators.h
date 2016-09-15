#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

#include "program2internals/ProgramInternals.h"
#include "ProgramInstance.hpp"
#include "program2internals/view/QtView.h"
#include "program2internals/model/Model.h"
#include "program2internals/controller/Controller.h"

#include <QTabWidget>

namespace ProgramInternalsCreators
{
    using LocalQtInstance = P2::Instance<P2::Controller::Controller<P2::Model::Model>, P2::View::QtView<P2::Input::InputPropagator>, P2::Input::InputPropagator, P2::Model::Model, P2::ProgramInternals<P2::Controller::Controller<P2::Model::Model>>, QWidget>;
    LocalQtInstance createLocalQt(QWidget *qtViewWidgetParent);
}

#endif // PROGRAMFACTORY_H
