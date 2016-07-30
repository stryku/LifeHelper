#pragma once

#include <Subprograms/HeartbeatController.hpp>

#include <string>
#include <functional>

namespace God
{
    namespace Subprograms
    {
        struct SignalsHandlers
        {
            std::function<void()> heartbeatLostCallback;
            std::function<void()> errorCallback;
            std::function<void()> cleanCloseCallback;
        };

        class SignalsHandler
        {
        public:
            SignalsHandler(const SignalsHandlers &handlers,
                           const std::string &addressToConnect, 
                           const std::string &subscriptionString) :
                heartbeatLostCallback{ handlers.heartbeatLostCallback },
                errorCallback{ handlers.errorCallback },
                cleanCloseCallback{ handlers.cleanCloseCallback },
                heartbeatController{ heartbeatLostCallback }
            {}

            void setHeartbeatLostCallback(std::function<void()> callback)
            {
                heartbeatLostCallback = callback;
            }

            void setErrorCallback(std::function<void()> callback)
            {
                errorCallback = callback;
            }

            void setCleanCloseCallback(std::function<void()> callback)
            {
                cleanCloseCallback = callback;
            }

        private:
            std::function<void()> heartbeatLostCallback;
            std::function<void()> errorCallback;
            std::function<void()> cleanCloseCallback;

            HeartbeatController heartbeatController;
        };
    }
}