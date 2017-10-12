#pragma once

#include "vector.hpp"

#include <vector>
#include <queue>
#include <memory>
#include <type_traits>

class Task {
public:
    virtual ~Task() {}

    virtual bool finished() const { return _finished; }
    virtual void update(double delta) = 0;

protected:
    bool _finished = false;
};

template <class T1, class... Ts>
struct AreTasks : std::bool_constant<
    std::is_base_of_v<Task, T1> && AreTasks<Ts>::value> {};

template <class T>
struct AreTasks<T> : std::bool_constant<std::is_base_of_v<Task, T>> {};

template <class T, class... Args>
std::unique_ptr<Task> task(Args&&... args)
{
    static_assert(AreTasks<Args...>(), "make can only make tasks");

    return std::make_unique<T>(std::forward<Args>(args)...);
}

class Wait : public Task {
public:
    Wait(double timeToWait) : _timeRemaining(timeToWait) {}

    void update(double delta) override
    {
        _timeRemaining -= delta;
        if (_timeRemaining <= 0) {
            _finished = true;
        }
    }

private:
    double _timeRemaining;
};

class Loop : public Task {
public:
    Loop(std::initializer_list<std::unique_ptr<Task>> tasks)
        : _tasks(tasks)
    { }

    void update(double delta) override
    {
        while (!_tasks.empty() && _tasks.front()->finished()) {
            _tasks.pop();
        }

        if (_tasks.empty()) {
            _finished = true;
            return;
        }

        _tasks.front()->update(delta);
    }

private:
    std::vector<std::unique_ptr<Task>> _tasks;
};