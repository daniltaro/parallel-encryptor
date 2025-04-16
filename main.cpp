#include <iostream>
#include <filesystem>
#include <string>
#include <list>
#include <thread>
#include "app/FileScanner/FileScanner.hpp"
#include "app/Tasks/Task.hpp"
#include "app/Tasks/TaskQueue.hpp"
#include "app/Crypter/Crypter.hpp"

void worker(TaskQueue &queue, const std::string &key) {
    Crypter crypter(key);
    while (!queue.empty()) {
        Task task = queue.pop();
        if (task.getStatus() == ENCRYPT)
            crypter.encrypt(task.getPath());
        else
            crypter.decrypt(task.getPath());
    }
}

int main() {
    std::string path;
    std::string stat;
    std::string key;
    Status status;

    std::cout << "Enter the path: ";
    std::getline(std::cin, path);

    std::cout << "Enter the status: ";
    std::getline(std::cin, stat);

    std::cout << "Enter the key: ";
    std::getline(std::cin, key);
    if (key.size() != 32) {
        throw std::runtime_error("Invalid key size");
    }
    if (stat == "encrypt") {
        status = ENCRYPT;
    } else if (stat == "decrypt") {
        status = DECRYPT;
    } else {
        throw std::invalid_argument("Invalid status");
    }

    try {
        if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
            TaskQueue tasks;
            FileScanner fileScanner(path);
            std::list<std::string> list_of_files = fileScanner.GetFileList();
            std::cout << "List of files: " << '\n';
            for (auto &file: list_of_files) {
                std::cout << file << '\n';
                Task task(file, status);
                tasks.push(task);
            }
            std::cout << '\n';

            std::vector<std::thread> threads;
            unsigned th_num = std::thread::hardware_concurrency();
            std::cout << "Hardware concurrency: " << th_num << '\n';


            for (int i = 0; i < th_num; ++i) {
                threads.emplace_back(worker, std::ref(tasks), std::ref(key));
            }

            for (auto &thread: threads) {
                thread.join();
            }
        }
    } catch (const std::filesystem::filesystem_error &e) {
        std::cout << e.what() << std::endl;
    }catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}