#pragma once
#include <chrono>

namespace config{
    static const auto ttl = std::chrono::milliseconds(10000);
    static const char addr[] = "0.0.0.0:9099";
}