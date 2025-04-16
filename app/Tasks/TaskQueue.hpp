#ifndef TASKQUEUE_HPP
#define TASKQUEUE_HPP

#include <queue>
#include <condition_variable>
#include "Task.hpp"

class TaskQueue {
private:
    std::queue<Task> tasks;
    std::mutex mutex;
    std::condition_variable cv;

public:
    void push(const Task &task);

    Task pop();

    bool empty();
};

#endif
