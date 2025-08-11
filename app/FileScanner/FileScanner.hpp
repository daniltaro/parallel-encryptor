#ifndef FILESCANNER_HPP
#define FILESCANNER_HPP

#include <string>
#include <list>

class FileScanner {
public:
    explicit FileScanner(const std::string &path_);

    std::list<std::string> GetFileList() const;

private:
    std::string path;
};

#endif
