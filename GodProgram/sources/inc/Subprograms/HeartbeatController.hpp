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
            HeartbeatController(HeartbeatController&&) = default;
            HeartbeatController& operator=(HeartbeatController&&) = default;

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

            std::function<void()> &heartbeatLostCallback;
            std::thread loopThread;

            std::chrono::time_point<Clock> lastBeat;
            std::chrono::milliseconds panicTime;
            std::chrono::milliseconds checkDuration;

            bool interrupted = false;
        };
    }
}