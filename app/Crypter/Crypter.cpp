#include "Crypter.hpp"
#include <iostream>
#include <thread>
#include <fstream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

void Crypter::encrypt(const std::string &path) {
    std::cout << "[Thread " << std::this_thread::get_id() << "] Encrypting file: " << path << '\n';
    std::ifstream infile(path, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file " + path + " for reading");
    }

    std::vector<unsigned char> input((std::istreambuf_iterator<char>(infile)),
                                     std::istreambuf_iterator<char>());
    infile.close();

    std::vector<unsigned char> key_data(key.begin(), key.end());
    if (key_data.size() != 32) {
        throw std::runtime_error("Invalid key size (must be 32 bytes for AES-256)");
    }

    std::vector<unsigned char> iv(16);
    if (!RAND_bytes(iv.data(), iv.size())) {
        throw std::runtime_error("Could not generate random IV");
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Could not create cipher context");
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_data.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptInit_ex failed");
    }

    std::vector<unsigned char> encrypted(input.size() + AES_BLOCK_SIZE);
    int out_len1 = 0;
    if (EVP_EncryptUpdate(ctx, encrypted.data(), &out_len1, input.data(), static_cast<int>(input.size())) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptUpdate failed");
    }

    int out_len2 = 0;
    if (EVP_EncryptFinal_ex(ctx, encrypted.data() + out_len1, &out_len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_EncryptFinal_ex failed");
    }
    EVP_CIPHER_CTX_free(ctx);

    std::ofstream outfile(path, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file " + path + " for writing");
    }
    outfile.write(reinterpret_cast<const char *>(iv.data()), iv.size());
    outfile.write(reinterpret_cast<const char *>(encrypted.data()), out_len1 + out_len2);
    outfile.close();
}

void Crypter::decrypt(const std::string &path) {
    std::cout << "[Thread " << std::this_thread::get_id() << "] Decrypting file: " << path << '\n';
    std::ifstream infile(path, std::ios::binary);
    if (!infile.is_open()) {
        throw std::runtime_error("Could not open file " + path + " for reading");
    }
    std::vector<unsigned char> input((std::istreambuf_iterator<char>(infile)),
                                     std::istreambuf_iterator<char>());
    infile.close();

    std::vector<unsigned char> key_data(key.begin(), key.end());
    if (key_data.size() != 32) {
        throw std::runtime_error("Invalid key size (must be 32 bytes for AES-256)");
    }

    std::vector<unsigned char> iv(16);
    for (int i = 0; i < 16; ++i) {
        iv[i] = input[i];
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Could not create cipher context");
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key_data.data(), iv.data()) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error(" EVP_DecryptInit_ex failed");
    }

    std::vector<unsigned char> decrypted(input.size() - 16);
    int out_len1 = 0;
    if (EVP_DecryptUpdate(ctx, decrypted.data(), &out_len1, input.data() + 16,
                          static_cast<int>(input.size()) - 16) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_DecryptUpdate failed");
    }

    int out_len2 = 0;
    if (EVP_DecryptFinal_ex(ctx, decrypted.data() + out_len1, &out_len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        throw std::runtime_error("EVP_DecryptFinal_ex failed");
    }
    EVP_CIPHER_CTX_free(ctx);

    std::ofstream outfile(path, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("Could not open file " + path + " for writing");
    }
    outfile.write(reinterpret_cast<const char *>(decrypted.data()), out_len1 + out_len2);
    outfile.close();
}

Crypter::Crypter(const std::string &key_): key(key_) {
}
