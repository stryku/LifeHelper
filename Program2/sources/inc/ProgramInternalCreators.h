#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

#include <internals/ProgramInternals.h>
#include <QWidget>

namespace ProgramInternalCreators
{
    ProgramInternals createLocalQt(QWidget *qtViewWidgetParent);
}

#endif // PROGRAMFACTORY_H
