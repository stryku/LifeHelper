#pragma once

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
                model.decrementSum();
            }

        private:
            std::weak_ptr<Model> model;
        };
    }
}
