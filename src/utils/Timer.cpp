#include "Timer.h"

Timer::Timer(float duration) : duration(duration), elapsedTime(0.0f), running(false) {}

void Timer::Start() {
    running = true;
    elapsedTime = 0.0f;
}

void Timer::Stop() {
    running = false;
}

void Timer::Reset() {
    elapsedTime = 0.0f;
    running = false;
}

void Timer::Update(float deltaTime) {
    if (running) {
        elapsedTime += deltaTime;
        if (elapsedTime >= duration) {
            running = false; // Detener el temporizador automáticamente
        }
    }
}

bool Timer::IsFinished() const {
    return elapsedTime >= duration;
}

float Timer::GetRemainingTime() const {
    return duration - elapsedTime;
}