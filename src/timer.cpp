#include "timer.hpp"

FrameTimer::FrameTimer(int fps)
    : _start(Clock::now())
    , _frameDurationSec(1.0 / fps)
    , _frameDuration(std::chrono::duration_cast<Clock::duration>(
        std::chrono::duration<double>(_frameDurationSec)))
    , _lastFrame(0)
{ }

double FrameTimer::frameDuration() const
{
    return _frameDurationSec;
}

int FrameTimer::framesPassed()
{
    auto now = Clock::now();
    auto currentFrame = (now - _start) / _frameDuration;
    auto frameDiff = currentFrame - _lastFrame;
    _lastFrame = currentFrame;
    return static_cast<int>(frameDiff);
}