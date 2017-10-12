#pragma once

#include "vector.hpp"
#include "random.hpp"
#include "tasks.hpp"

#include <random>

class IdleMovement {
public:
    IdleMovement()
    {
        Vector<double> randomPoint;
        std::normal_distribution<double> dis();

        _task = task<Loop>(
            task<Wait>(10.0),
            task<Execute>(selectRandomPoint),
            task<GoToPoint>(randomPoint)
        );
    }

private:
    void selectRandomPoint()
    {
        _randomPoint = {_dis(random::gen()), _dis(random::gen())};
    }

    std::normal_distribution<double> _dis;
    std::unique_ptr<Task> _task;

    Vector<double> _randomPoint;
};

