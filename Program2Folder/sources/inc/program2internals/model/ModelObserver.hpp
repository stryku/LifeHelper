#pragma once

#include "utils/log.hpp"

#include <memory>

namespace P2
{
    namespace Model
    {
        template <typename View>
        class ModelObserver
        {
        public:
            ModelObserver() = default;
            ModelObserver(ModelObserver&&) = default;
            ModelObserver& operator=(ModelObserver&&) = default;

            ModelObserver(const ModelObserver&) = delete;
            ModelObserver& operator=(const ModelObserver&) = delete;

            void registerView(std::weak_ptr<View> view)
            {
                LOG_FILE("ModelObserver::registerView");

                views.push_back(view);
            }

            void newSumValue(size_t newSum)
            {
                LOG_FILE("ModelObserver::newSumValue");

                for (auto &weakView : views)
                    if (auto view = weakView.lock())
                        view->updateSum(newSum);
            }

        private:
            std::vector<std::weak_ptr<View>> views;
        };
    }
}
