#include "hasher.h"

#include <openssl/evp.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <array>
#include <iomanip>

Hasher::Hasher() {
    ctx = EVP_MD_CTX_new();

    if (!ctx) {
        throw std::runtime_error("OpenSSL: EVP_MD_CTX_new failed");
    }
}

Hasher::~Hasher() {
    if (ctx) {
        EVP_MD_CTX_free(ctx);
    }
}

std::string Hasher::md5_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }


    if (!EVP_DigestInit_ex(ctx, EVP_md5(), nullptr)) {
        throw std::runtime_error("OpenSSL: EVP_DigestInit_ex failed");
    }

    std::array<char, 4096> buffer;

    while (file) {
        // читаем файл частями, чтобы не загружать весь в память
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes = file.gcount();

        if (bytes > 0) {
            // добавляем очередной блок данных в хэш
            if (!EVP_DigestUpdate(ctx, buffer.data(), bytes)) {
                throw std::runtime_error("OpenSSL: EVP_DigestUpdate failed for file: " + path.string());
            }
            
        }
    }

    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;

    // получаем итоговый MD5 (16 байт)
    if (!EVP_DigestFinal_ex(ctx, result, &len)) {
        throw std::runtime_error("OpenSSL: EVP_DigestFinal_ex failed");
    }

    static const char* hex = "0123456789abcdef";

    std::string out;
    out.resize(len * 2);

    for (unsigned i = 0; i < len; i++) {
        unsigned char b = result[i];
        out[i * 2]     = hex[b >> 4];
        out[i * 2 + 1] = hex[b & 0x0F];
    }

    return out;
}