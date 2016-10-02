#pragma once

#include "utils/log.hpp"

#include "memory"

namespace P2
{
    namespace Input
    {
        template <typename Model>
        class InputHandler
        {
        public:
            InputHandler(std::weak_ptr<Model> model)
                : model{ model }
            {}

            void decrementSum() 
            {
                if (auto ptr = model.lock())
                    ptr->decrementSum();
                else
                    LOG_FILE("InputHandler::model expired");
            }

        private:
            std::weak_ptr<Model> model;
        };
    }
}
