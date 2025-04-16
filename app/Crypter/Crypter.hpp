#ifndef CRYPTER_HPP
#define CRYPTER_HPP

#include <string>

class Crypter {
private:
    std::string key;

public:
    Crypter(const std::string &key_);

    void encrypt(const std::string &path);

    void decrypt(const std::string &path);
};

#endif
