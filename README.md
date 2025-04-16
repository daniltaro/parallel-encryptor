# Parallel Encryptor

A multithreaded AES-256-CBC file encryptor and decryptor written in C++ using OpenSSL.

## Features

- 🔐 AES-256 encryption with random IV for each file
- ⚡ Fast and parallel processing using multiple threads
- 📂 Recursively scans directories for files
- 💾 Works with **any file type** (binary-safe)

## Usage

1. Clone the repo and build using CMake:

```bash
mkdir build && cd build
cmake ...
```

2.	Run the program:
```
./Parallel_Encryptor
```

3.	Input path, mode (encrypt or decrypt), and a 32-character key.

Example
```bash
Enter the path: /home/user/files
Enter the status: encrypt
Enter the key: 12345678901234567890123456789012
```
## Notes
- Make sure OpenSSL is installed.
- Your key must be 32 characters long for AES-256.
- Encrypted files store the IV at the beginning.
