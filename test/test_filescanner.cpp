#include <gtest/gtest.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <../../app/FileScanner/FileScanner.hpp>

namespace fs = std::filesystem;

void create_file(const fs::path& p) { std::ofstream o{p}; }

class FileScannerTest : public testing::Test {
protected:
    const fs::path dir{"tmp_dir"};
    FileScanner file_scanner{"tmp_dir"};

    void SetUp()override {
        fs::create_directory(dir);
        create_file(dir / "one");
        create_file(dir / "two");
        create_file(dir / "three");
    }

    void TearDown() override {
        fs::remove_all(dir);
    }
};

TEST_F(FileScannerTest, GetFileListTest){
    std::list<std::string> list = {"tmp_dir/one", "tmp_dir/two", "tmp_dir/three"};
    std::list<std::string> list2 = file_scanner.GetFileList();

    list.sort();
    list2.sort();

    EXPECT_EQ(list, list2);
}

TEST_F(FileScannerTest, EmptyGetFileListTest){
    fs::remove_all(dir);
    fs::create_directory(dir);
    std::list<std::string> list = file_scanner.GetFileList();

    EXPECT_TRUE(list.empty());
}

TEST(FileScanner, NotExistDirTest){
    FileScanner fs{"not_exist"};
    EXPECT_THROW(fs.GetFileList(), std::filesystem::filesystem_error);
}