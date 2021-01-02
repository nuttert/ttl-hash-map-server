#pragma once
#include <concepts>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace l1_memory_cache{
    class WorkerInterface{
       public:
            virtual ~WorkerInterface() = default;

            virtual void Run() = 0;
            virtual void Stop() = 0;
       private:
            
    };
}
