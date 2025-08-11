#ifndef CRYPTER_HPP
#define CRYPTER_HPP

#include <string>
#include <mutex>

class Crypter {
private:
    std::string key;

public:
    explicit Crypter(const std::string& key_);

    void encrypt(const std::string &path);

    void decrypt(const std::string &path);
};

#endif
