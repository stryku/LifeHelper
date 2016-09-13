#pragma once

#include "tiny_process_library/process.hpp"

#include <utility>

namespace God
{
    namespace Subprograms
    {
        namespace Process
        {
            class Factory
            {
            public:
                static tpl::Process create()
                {
                    return std::move(tpl::Process{ "C:/moje/programowanie/LifeController/bin/programs/Program2/Program2.exe", "" });
                }
            };
        }
    }
}