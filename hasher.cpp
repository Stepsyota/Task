#include "hasher.h"

#include <openssl/evp.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <array>


std::string md5_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    // создаём контекст MD5 (EVP — универсальный API OpenSSL)
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (!ctx) {
        throw std::runtime_error("Failed to create EVP context");
    }

    EVP_DigestInit_ex(ctx, EVP_md5(), nullptr);

    std::array<char, 4096> buffer;

    while (file.good()) {
        // читаем файл частями, чтобы не загружать весь в память
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes = file.gcount();

        if (bytes > 0) {
            // добавляем очередной блок данных в хэш
            EVP_DigestUpdate(ctx, buffer.data(), bytes);
        }
    }

    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;

    // получаем итоговый MD5 (16 байт)
    EVP_DigestFinal_ex(ctx, result, &len);
    EVP_MD_CTX_free(ctx);

    std::ostringstream oss;

    // переводим бинарный хэш в читаемую hex-строку
    for (unsigned int i = 0; i < len; i++) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << (int)result[i];
    }

    return oss.str();
}