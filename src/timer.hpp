#pragma once

#include <chrono>

class FrameTimer {
public:
    FrameTimer(int fps);

    /**
     * Duration of one frame, in seconds
     */
    double frameDuration() const;

    /**
     * Check how many frames passed since last call of this function, or start
     * of the timer.
     */
    int framesPassed();

private:
    using Clock = std::chrono::high_resolution_clock;

    const Clock::time_point _start;
    const double _frameDurationSec;
    const Clock::duration _frameDuration;
    long long _lastFrame;
};