#pragma once

#include <chrono>

class Timer{
public:
    void Start();
    void End();
    double GetDuration() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> _t1;
    std::chrono::time_point<std::chrono::steady_clock> _t2;
};
