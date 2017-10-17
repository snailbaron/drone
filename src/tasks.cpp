#include "tasks.hpp"

#include <cassert>

QuickTask::QuickTask(std::function<std::function<Status(double)>()> generator)
    : _generator(generator)
{ }

QuickTask::QuickTask(std::function<Status(double)> action)
    : _generator([action]{ return action; })
{ }

QuickTask::QuickTask(std::function<void()> action)
    : _generator([action] {
            return [action](double) {
                action();
                return Status::Success;
            };
        })
{ }

void QuickTask::initialize()
{
    _action = _generator();
}

Task::Status QuickTask::update(double delta)
{
    return _action(delta);
}

void QuickTask::finalize()
{
    _action = {};
}

void TaskList::initialize()
{
    _current = _tasks.begin();
    currentTask().initialize();
}

void TaskList::finalize()
{
}

Task::Status Sequence::update(double delta)
{
    auto status = currentTask().update(delta);
    switch (status) {
        case Status::Running:
            return Status::Running;

        case Status::Failure:
            currentTask().finalize();
            return Status::Failure;

        case Status::Success:
            currentTask().finalize();
            next();

            if (done()) {
                return Status::Success;
            } else {
                currentTask().initialize();
                return Status::Running;
            }
    }
    return Status::Failure;
}

Task::Status Select::update(double delta)
{
    auto status = currentTask().update(delta);
    switch (status) {
        case Status::Running:
            return Status::Running;

        case Status::Failure:
            currentTask().finalize();
            next();
            if (done()) {
                return Status::Failure;
            } else {
                currentTask().initialize();
                return Status::Running;
            }

        case Status::Success:
            currentTask().finalize();
            return Status::Success;
    }
    return Status::Failure;
}
