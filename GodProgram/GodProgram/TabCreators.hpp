#pragma once

#include <program2internals/view/detail/QtWidgetManager.h>

#include <QWidget>

namespace God
{
    namespace Creators
    {
        namespace Tab
        {
            std::unique_ptr<P2::View::detail::QtWidgetManager> createProgram2(QWidget *parent)
            {
                //static constexpr auto uiPath = "programs/Program2/";

                return std::make_unique<P2::View::detail::QtWidgetManager>(parent, "programs/Program2/uiforms/Program2Form.ui");
            }
        }
    }
}
