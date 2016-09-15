#pragma once

#include "tiny_process_library\\process.hpp"
#include "utils\\log.hpp"

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
                    try
                    {
                        return std::move(tpl::Process{ "C:\\moje\\programowanie\\LifeController\\bin\\programs\\Program2\\Program2.exe", ""
                        });
                    }
                    catch (std::exception &e)
                    {
                        LOG("Process::Factory::create exception caught: " << e.what());
                    }
                }
            };
        }
    }
}