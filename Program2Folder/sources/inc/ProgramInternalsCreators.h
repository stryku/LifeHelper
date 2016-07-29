#ifndef PROGRAMFACTORY_H
#define PROGRAMFACTORY_H

#include <program2internals/ProgramInternals.h>
#include <QWidget>

namespace ProgramInternalsCreators
{
    ProgramInternals createLocalQt(QWidget *qtViewWidgetParent);
}

#endif // PROGRAMFACTORY_H
