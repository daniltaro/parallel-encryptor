cmake_minimum_required(VERSION 3.30)
project(Parallel_Encryptor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenSSL REQUIRED)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
)

add_executable(Parallel_Encryptor app/main.cpp
        app/FileScanner/FileScanner.cpp
        app/FileScanner/FileScanner.hpp
        app/Tasks/Task.cpp
        app/Tasks/Task.hpp
        app/Tasks/TaskQueue.cpp
        app/Tasks/TaskQueue.hpp
        app/Crypter/Crypter.cpp
        app/Crypter/Crypter.hpp
)

add_executable(tests 
        test/test_filescanner.cpp
        app/FileScanner/FileScanner.cpp
        app/FileScanner/FileScanner.hpp
)

target_link_libraries(Parallel_Encryptor OpenSSL::Crypto)

target_link_libraries(
    tests PRIVATE
    gtest gtest_main
)