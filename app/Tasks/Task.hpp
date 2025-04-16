#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <iostream>

enum Status {
    ENCRYPT = 0,
    DECRYPT = 1,
};

class Task {
private:
    std::string path;
    Status status;

public:
    Task(const std::string &_path, Status _status);

    const std::string &getPath() const;

    const Status getStatus() const;
};

#endif
