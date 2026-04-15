#pragma once

#include <string>
#include <filesystem>


/**
 * @brief Вычисляет MD5 хэш файла
 *
 * Функция читает файл в бинарном режиме потоково,
 * чтобы корректно обрабатывать файлы любого размера без загрузки в память.
 *
 * Используется OpenSSL.
 *
 * @param path путь к файлу
 * @return MD5 хэш файла в виде hex-строки
 *
 * @throws std::runtime_error если файл не открылся или не удалось создать контекст EVP
 */
std::string md5_file(const std::filesystem::path& path);