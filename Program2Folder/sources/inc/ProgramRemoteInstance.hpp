#pragma once

#include "ProgramInstance.hpp"

namespace P2
{
    template <typename BaseInstance, typename MessageHandler, typename MessageReceiver>
    class ProgramRemoteInstance
    {
    public:
        ProgramRemoteInstance(BaseInstance &&baseInstance)
            : baseInstance{ std::move(baseInstance) }
        {}

        ProgramRemoteInstance(ProgramRemoteInstance&&) = default;
        ProgramRemoteInstance& operator=(ProgramRemoteInstance&&) = default;

        ProgramRemoteInstance() = delete;
        ProgramRemoteInstance(const ProgramRemoteInstance&) = delete;
        ProgramRemoteInstance& operator=(const ProgramRemoteInstance&) = delete;



    private:
        BaseInstance baseInstance;
    };
}
