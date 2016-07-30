#pragma once

#include <Subprograms/helpers.hpp>
#include <Tabs/TabCreators.hpp>

#include <QTabWidget>

#include <unordered_map>
#include <memory>

namespace God
{
    namespace Tabs
    {
        class TabsManager
        {
        public:
            TabsManager() = default;
            TabsManager(QTabWidget *tabWidget) :
                tabWidget{ tabWidget }
            {};
            ~TabsManager() = default;
            TabsManager(TabsManager &&) = default;
            TabsManager& operator=(TabsManager &&) = default;

            TabsManager(const TabsManager&) = delete;
            TabsManager& operator=(const TabsManager&) = delete;

            void setTabWidget(QTabWidget *newTabWidget)
            {
                tabWidget = newTabWidget;
            }

            void create(Subprograms::Type type,
                        Subprograms::ModelId modelId,
                        size_t index = DefaultTabIndex);

        private:
            static constexpr size_t DefaultTabIndex = -1;

            void createProgram2Tab(Subprograms::ModelId modelId, size_t index);

            QTabWidget *tabWidget = nullptr;
            std::unordered_map<Subprograms::ModelId, std::vector<std::unique_ptr<P2::View::detail::QtWidgetManager>>> programs2Map;
        };
    }
}