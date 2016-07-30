#pragma once

#include <Subprograms/HeartbeatController.hpp>

#include <string>
#include <functional>

namespace God
{
    namespace Subprograms
    {
        enum class SignalType
        {
            HEARTBEAT_SIGNAL,
            ERROR_SIGNAL,
            CLEAN_CLOSE_SIGNAL
        };

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
                           const std::string &subscriptionString) noexcept :
                heartbeatLostCallback{ handlers.heartbeatLostCallback },
                errorCallback{ handlers.errorCallback },
                cleanCloseCallback{ handlers.cleanCloseCallback },
                heartbeatController{ heartbeatLostCallback }
            {}

            void setHeartbeatLostCallback(std::function<void()> callback) noexcept
            {
                heartbeatLostCallback = callback;
            }

            void setErrorCallback(std::function<void()> callback) noexcept
            {
                errorCallback = callback;
            }

            void setCleanCloseCallback(std::function<void()> callback) noexcept
            {
                cleanCloseCallback = callback;
            }

            template <typename ...Args>
            void signal(SignalType type, Args... args)
            {
                switch (type)
                {
                case God::Subprograms::SignalType::HEARTBEAT_SIGNAL:
                    handleHeartbeat();
                    break;

                case God::Subprograms::SignalType::ERROR_SIGNAL:
                    handleError(std::forward<Args>(args...));
                    break;

                case God::Subprograms::SignalType::CLEAN_CLOSE_SIGNAL:
                    handleCleanClose();
                    break;

                default:
                    //todo log
                    break;
                }
            }

        private:
            void handleHeartbeat()
            {
                heartbeatController.beat();
            }

            void handleError(const std::string &errorMsg)
            {}

            void handleCleanClose()
            {}

            std::function<void()> heartbeatLostCallback;
            std::function<void()> errorCallback;
            std::function<void()> cleanCloseCallback;

            HeartbeatController heartbeatController;
        };
    }
}