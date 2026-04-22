#pragma once

#include <string>
#include <filesystem>
#include <openssl/evp.h>

class Hasher {
    public:
        Hasher();
        ~Hasher();


        /**
        * @brief Вычисляет MD5 хэш файла
        *
        * Функция читает файл в бинарном режиме потоково,
        * чтобы корректно обрабатывать файлы любого размера без загрузки в память.
        *
        * Используется OpenSSL.
        *
        * @param path путь к файлу
        * @return MD5 хэш файла в виде hex-строки (32 символа, lowercase)
        *
        * @throws std::runtime_error если файл не открылся или произошла ошибка с OpenSSL методами
        */
        std::string md5_file(const std::filesystem::path& path);

    private:
        EVP_MD_CTX* ctx;
};