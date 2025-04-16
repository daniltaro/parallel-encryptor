cmake_minimum_required(VERSION 3.30)
project(Parallel_Encryptor)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)

add_executable(Parallel_Encryptor main.cpp
        app/FileScanner/FileScanner.cpp
        app/Tasks/Task.cpp
        app/Tasks/TaskQueue.cpp
        app/Crypter/Crypter.cpp
        app/Crypter/Crypter.hpp)

target_link_libraries(Parallel_Encryptor OpenSSL::Crypto)