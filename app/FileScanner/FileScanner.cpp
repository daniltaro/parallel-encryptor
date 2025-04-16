#include "FileScanner.hpp"
#include <filesystem>

FileScanner::FileScanner(const std::string &path_): path(path_) {
}

std::list<std::string> FileScanner::GetFileList() const {
    std::list<std::string> files;
    for (const std::filesystem::directory_entry &dir_entry:
         std::filesystem::recursive_directory_iterator(path)) {
        if (dir_entry.is_regular_file()) {
            files.push_back(dir_entry.path().string());
        }
    }
    return files;
}
