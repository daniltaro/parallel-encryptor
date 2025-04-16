#include "Task.hpp"

const std::string &Task::getPath() const {
    return path;
}

const Status Task::getStatus() const {
    return status;
}

Task::Task(const std::string &_path, Status _status) : path(_path), status(_status) {
}
