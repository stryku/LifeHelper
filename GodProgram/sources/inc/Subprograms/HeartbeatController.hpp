#pragma once

#include <functional>
#include <chrono>
#include <thread>

namespace God
{
    namespace Subprograms
    {
        class HeartbeatController
        {
        private:
            using ms = std::chrono::milliseconds;
        public:
            HeartbeatController(std::function<void()> &heartbeatLostCallback, 
                                const ms &panicTime = ms{5000},
                                const ms &checkDuration = ms{ 1000 }) noexcept :
                heartbeatLostCallback{ heartbeatLostCallback }
            {}

            ~HeartbeatController() = default;

            HeartbeatController(HeartbeatController &&other) :
                heartbeatLostCallback{ std::move(other.heartbeatLostCallback) },
                loopThread{ std::move(other.loopThread) },
                lastBeat{ std::move(other.lastBeat) },
                panicTime{ std::move(other.panicTime) },
                checkDuration{ std::move(other.checkDuration) }
            {}

            HeartbeatController& operator=(HeartbeatController &&other)
            {
                heartbeatLostCallback = std::move(other.heartbeatLostCallback);
                loopThread = std::move(other.loopThread);
                lastBeat = std::move(other.lastBeat);
                panicTime = std::move(other.panicTime);
                checkDuration = std::move(other.checkDuration);

                return *this;
            }

            HeartbeatController(const HeartbeatController&) = delete;
            HeartbeatController& operator=(const HeartbeatController&) = delete;

            void interrupt() noexcept
            {
                interrupted = true;
            }

            void beat() noexcept
            {
                lastBeat = Clock::now();
            }

            void start()
            {
                auto loop = [this]
                {
                    while (!interrupted)
                    {
                        if (Clock::now() - lastBeat > panicTime)
                            heartbeatLostCallback();

                        std::this_thread::sleep_for(checkDuration);
                    }
                };

                lastBeat = Clock::now();

                loopThread = std::thread{ loop };
            }

        private:
            using Clock = std::chrono::system_clock;

            std::reference_wrapper<std::function<void()>> heartbeatLostCallback;
            std::thread loopThread;

            std::chrono::time_point<Clock> lastBeat;
            std::chrono::milliseconds panicTime;
            std::chrono::milliseconds checkDuration;

            bool interrupted = false;
        };
    }
}