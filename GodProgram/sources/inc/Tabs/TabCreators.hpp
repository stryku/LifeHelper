#pragma once

#include <program2internals/view/detail/QtWidgetManager.h>

#include <QWidget>

#include <memory>

namespace God
{
    namespace Tabs
    {
        namespace Creators
        {
            std::unique_ptr<P2::View::detail::QtWidgetManager> createProgram2(QWidget *parent);
        }
    }
}
