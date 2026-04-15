#pragma once

#include <filesystem>
#include <unordered_set>



/**
 * @brief Загружает данные из текстовых файлов
 */
class ValuesReader {
public:
    /**
     * @brief Загружает последовательности символов из файла в множество
     * 
     * @param path путь к файлу
     * @return множество строк
     * @throw std::runtime_error если файл не открылся
     */
    static std::unordered_set<std::string> load_hashes_to_set(const std::filesystem::path& path);

    /**
     * @brief Загружает расширения из файла в множество, нормализуя их
     * 
     * @param path путь к файлу
     * @return множество строк
     * @throw std::runtime_error если файл не открылся
     */
    static std::unordered_set<std::string> load_extensions_to_set(const std::filesystem::path& path);
};