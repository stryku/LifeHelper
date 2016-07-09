#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

#include <internals/ProgramInternals.h>
#include <internals/view/P2QtView.h>
#include <QWidget>

namespace ProgramFactory
{
    ProgramInternals createLocalQt(QWidget *qtViewWidgetParent);
}

#endif // PROGRAMFACTORY_H
