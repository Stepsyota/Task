#include "hasher.h"

#include <openssl/evp.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <array>
#include <iomanip>

std::string md5_file(const std::filesystem::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    // создаём контекст MD5 (EVP — универсальный API OpenSSL)
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>
        ctx(EVP_MD_CTX_new(), EVP_MD_CTX_free);

    if (!ctx) {
        throw std::runtime_error("OpenSSL: EVP_MD_CTX_new failed");
    }

    if (!EVP_DigestInit_ex(ctx.get(), EVP_md5(), nullptr)) {
        throw std::runtime_error("OpenSSL: EVP_DigestInit_ex failed");
    }

    std::array<char, 4096> buffer;

    while (file) {
        // читаем файл частями, чтобы не загружать весь в память
        file.read(buffer.data(), buffer.size());
        std::streamsize bytes = file.gcount();

        if (bytes > 0) {
            // добавляем очередной блок данных в хэш
            if (!EVP_DigestUpdate(ctx.get(), buffer.data(), bytes)) {
                throw std::runtime_error("OpenSSL: EVP_DigestUpdate failed for file: " + path.string());
            }
            
        }
    }

    unsigned char result[EVP_MAX_MD_SIZE];
    unsigned int len = 0;

    // получаем итоговый MD5 (16 байт)
    if (!EVP_DigestFinal_ex(ctx.get(), result, &len)) {
        throw std::runtime_error("OpenSSL: EVP_DigestFinal_ex failed");
    }

    std::ostringstream oss;

    // переводим бинарный хэш в читаемую hex-строку
    oss << std::hex << std::setfill('0');
    for (unsigned int i = 0; i < len; i++) {
        oss << std::setw(2) << static_cast<int>(result[i]);
    }

    return oss.str();
}