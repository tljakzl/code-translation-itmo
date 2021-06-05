//
// Created by kozlov-an on 03.06.2021.
//

#include "Timer.h"

double Timer::GetDuration() const{
    const std::chrono::duration<double, std::milli> ms = _t2 - _t1;
    return ms.count();
}

void Timer::End(){
    _t2 = std::chrono::high_resolution_clock::now();
}

void Timer::Start(){
    _t1 = std::chrono::high_resolution_clock::now();
}
