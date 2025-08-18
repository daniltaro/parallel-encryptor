#include <gtest/gtest.h>
#include <../app/Crypter/Crypter.hpp>
#include <fstream>
#include <string>


class CrypterTest : public testing::Test {
protected:
    std::fstream stream;
    Crypter crypter{"12345678901234567890123456789012"};

    void SetUp() override {
        stream.open("tempfile.txt", std::ios::trunc | std::ios::out);
        stream << "Some data.\nSome data again!";
        stream.close();
    }

    void TearDown() override {
        std::remove("tempfile.txt");
    }
};

std::string read_file(const std::string&& file, std::fstream& stream){
    stream.open(file, std::ios::in);
    std::string line, str;
    while(std::getline(stream, line)){
        str += line + "\n";
    }
    stream.close();

    return str;
}

TEST_F(CrypterTest, EncryptDecryptTest){
    crypter.encrypt("tempfile.txt");

    std::string expected = "Some data.\nSome data again!\n";

    std::string str = read_file("tempfile.txt", stream);
    EXPECT_NE(str, expected);

    crypter.decrypt("tempfile.txt");
    
    str = read_file("tempfile.txt", stream);
    EXPECT_EQ(str, expected);
}

