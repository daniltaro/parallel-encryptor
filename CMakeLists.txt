cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Parallel_Encryptor)

#   PROJECT
find_package(OpenSSL REQUIRED)

add_library(core_lib STATIC
    app/FileScanner/FileScanner.cpp
    app/Tasks/Task.cpp
    app/Tasks/TaskQueue.cpp
    app/Crypter/Crypter.cpp
)

target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/app)
target_link_libraries(core_lib PUBLIC OpenSSL::Crypto)

add_executable(Parallel_Encryptor app/main.cpp)
target_link_libraries(Parallel_Encryptor PRIVATE core_lib)

#   TESTS
find_package(GTest)
if(GTest_FOUND)
    add_executable(
        tests
        test/test_filescanner.cpp
        test/test_crypter.cpp
    )

    target_include_directories(tests PRIVATE ${GTEST_INCLUDE_DIRS})
    target_link_libraries(tests PRIVATE core_lib GTest::gtest_main GTest::gtest)
endif()