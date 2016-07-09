#ifndef VIEWFACTORY_H
#define VIEWFACTORY_H

#include <internals/view/P2View.h>
#include <internals/view/P2QtView.h>

namespace ViewFactory
{
    enum class ViewType
    {
        QT,
        CONSOLE,
        REMOTE
    };

    static P2View* createView(ViewType type)
    {
        switch(type)
        {
//            case ViewType::QT:

        }

        return nullptr;
    }

    P2QtView* createQtView()
    {
        return nullptr;
    }
}

#endif // VIEWFACTORY_H
