#include <internals/view/detail/P2QtWidgetManager.h>

P2QtWidgetManager::P2QtWidgetManager(QWidget *parent) :
    formWidget(createWidget(parent))
{
}
