#pragma once
#include <atomic>
#include <concepts>
#include <chrono>
#include <future>
#include "worker-interface.hpp"

namespace l1_memory_cache{
    class Worker: public WorkerInterface{
        using Future = std::future<void>;
        using Callback = std::function<void ()>;
       public:
            Worker(const Callback& callback, const std::chrono::milliseconds& period);
            void Run() override;
            void Stop() override;

            ~Worker();
        private:
            Callback callback_;
            std::chrono::milliseconds period_;

            Future future_;
            std::atomic_bool is_running_;
    };
}