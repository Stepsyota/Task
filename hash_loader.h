#pragma once

#include <filesystem>
#include <unordered_set>



/**
 * @brief Загружает данные из текстовых файлов
 */
class HashLoader {
public:
    /**
     * @brief Загружает последовательности символов из файла в множество
     * 
     * @param path путь к файлу
     * @return множество строк
     */
    static std::unordered_set<std::string> load_words_to_set(const std::filesystem::path& path);
};