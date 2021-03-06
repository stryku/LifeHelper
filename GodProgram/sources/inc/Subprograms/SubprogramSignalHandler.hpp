#pragma once

#include "communication/messages/SignalType.hpp"
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
            std::function<void(const std::string&)> errorCallback;
            std::function<void()> cleanCloseCallback;
        };

        class SignalsHandler
        {
        public:
            SignalsHandler(const SignalsHandlers &handlers) noexcept :
                heartbeatLostCallback{ handlers.heartbeatLostCallback },
                errorCallback{ handlers.errorCallback },
                cleanCloseCallback{ handlers.cleanCloseCallback },
                heartbeatController{ heartbeatLostCallback }
            {}

            SignalsHandler(SignalsHandler &&other) = default;
            SignalsHandler& operator=(SignalsHandler &&other) = default;

            SignalsHandler(SignalsHandler&) = delete;
            SignalsHandler& operator=(SignalsHandler&) = delete;

            void setHeartbeatLostCallback(std::function<void()> callback) noexcept
            {
                heartbeatLostCallback = callback;
            }

            void setErrorCallback(std::function<void(const std::string&)> callback) noexcept
            {
                errorCallback = callback;
            }

            void setCleanCloseCallback(std::function<void()> callback) noexcept
            {
                cleanCloseCallback = callback;
            }

            template <typename SignalType, typename ...Args>
            void signal(SignalType type, Args... args)
            {
                switch (type)
                {
                case Common::Communication::SignalType::Type::HEARTBEAT_SIGNAL:
                    handleHeartbeat();
                    break;

                case Common::Communication::SignalType::Type::ERROR_SIGNAL:
                    handleError(std::forward<Args>(args)...);
                    break;

                case Common::Communication::SignalType::Type::CLEAN_CLOSE_SIGNAL:
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
            std::function<void(const std::string&)> errorCallback;
            std::function<void()> cleanCloseCallback;

            HeartbeatController heartbeatController;
        };
    }
}