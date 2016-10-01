#include <Tabs/TabsManager.hpp>

using namespace God;
using namespace God::Tabs;


void TabsManager::createProgram2Tab(Subprograms::ModelId modelId, size_t index)
{
    auto p2WidgetMngr = Creators::createProgram2(tabWidget);

    if (index == DefaultTabIndex)
        index = tabWidget->count() - 1;

    tabWidget->insertTab(index, p2WidgetMngr->getWidget(), "Program2");

    programs2Map[modelId].emplace_back(std::move(p2WidgetMngr));
}


void TabsManager::create(Subprograms::Type type,
                         Subprograms::ModelId modelId,
                         size_t index)
{
    switch (type)
    {
    case God::Subprograms::Type::P2:
        createProgram2Tab(modelId, index);
        break;

    default:
        break;
    }
}