#include <Tabs/TabCreators.hpp>

namespace God
{
    namespace Tabs
    {
        namespace Creators
        {
            std::unique_ptr<P2::View::detail::QtWidgetManager> createProgram2(QWidget *parent)
            {
                return std::make_unique<P2::View::detail::QtWidgetManager>(parent, "programs/Program2/uiforms/Program2Form.ui");
            }
        }
    }
}