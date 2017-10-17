#pragma once

#include "utils.hpp"

#include <initializer_list>
#include <memory>
#include <vector>
#include <functional>
#include <any>
#include <type_traits>

class Task {
public:
    enum class Status {
        Running,
        Success,
        Failure,
    };

    virtual ~Task() {}

    virtual void initialize() {}
    virtual Status update(double delta) = 0;
    virtual void finalize() {}
};

class QuickTask : public Task {
public:
    QuickTask(std::function<std::function<Status(double)>()> generator);
    QuickTask(std::function<Status(double)> action);
    QuickTask(std::function<void()> action);

    void initialize() override;
    Status update(double delta) override;
    void finalize() override;

private:
    std::function<std::function<Status(double)>()> _generator;
    std::function<Status(double)> _action;
};

class TaskList : public Task {
public:
    template <class... Ts>
    TaskList(Ts&&... tasks)
    {
        static_assert(std::conjunction<std::is_base_of<Task, Ts>...>(),
            "TaskList may only accept Tasks in constructor");

        copyToPtrContainer(_tasks, std::forward<Ts>(tasks)...);
        _current = _tasks.end();
    }

    void initialize() override;
    void finalize() override;

protected:
    Task& currentTask() { return **_current; }
    void next() { _current++; }
    bool done() { return _current == _tasks.end(); }

private:
    using TaskVector = std::vector<std::unique_ptr<Task>>;

    TaskVector _tasks;
    TaskVector::iterator _current;
};

class Sequence : public TaskList {
public:
    template <class... Tasks>
    Sequence(Tasks&&... tasks) : TaskList(std::forward<Tasks>(tasks)...) {}

    Status update(double delta) override;
};

class Select : public TaskList {
public:
    template <class... Tasks>
    Select(Tasks&&... tasks) : TaskList(std::forward<Tasks>(tasks)...) {}

    Status update(double delta) override;
};
