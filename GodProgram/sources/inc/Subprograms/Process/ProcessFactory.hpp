#pragma once

#include "Subprograms/helpers.hpp"
#include "tiny_process_library/process.hpp"
#include "utils/log.hpp"
#include "utils/ToString.hpp"

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
                static tpl::Process create(ModelId id)
                {
                    try
                    {
                        auto command = createCommand(id);
                        LOG_FILE("Process::Facroty creating with command: " << command);
                        return std::move(tpl::Process{ command.c_str(), "" });
                    }
                    catch (std::exception &e)
                    {
                        LOG("Process::Factory::create exception caught: " << e.what());
                    }
                }

            public:
                static std::string createCommand(ModelId id)
                {
                    std::string programPath = "C:\\moje\\programowanie\\LifeController\\bin\\programs\\Program2\\Program2.exe";
                    std::string address = "tcp://127.0.0.1:1777";
                    std::string modelId = utils::toString(id);

                    return programPath + " remote " +
                           address + " " +
                           modelId;
                }
            };
        }
    }
}