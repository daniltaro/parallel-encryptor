#include "TaskQueue.hpp"

void TaskQueue::push(const Task &task) {
    std::unique_lock<std::mutex> lock(mutex);
    tasks.push(task);
    cv.notify_one();
}

Task TaskQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    cv.wait(lock, [&] { return !tasks.empty(); });
    Task task = tasks.front();
    tasks.pop();
    return task;
}

bool TaskQueue::empty() {
    std::unique_lock<std::mutex> lock(mutex);
    return tasks.empty();
}
