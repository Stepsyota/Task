#pragma once

#include <iostream>
#include <filesystem>


/**
 * @brief Хранит пути, переданные через аргументы командной строки
 */
struct Config {
    std::filesystem::path scan_directory;   //< Директория для сканирования
    std::filesystem::path white_list_file;  //< Файл белого списка
    std::filesystem::path black_list_file;  //< Файл черного списка
    std::filesystem::path extensions_file;  //< Файл расширений
};

/**
 * @brief Парсит аргументы командной строки в структуру Config
 */
class ConfigParser {
    public:

        /**
        * @brief Заполняет Config из аргументов командной строки
        * 
        * @param argc Количество аргументов
        * @param argv Массив аргументов
        * @param cfg Структура конфигурации для заполнения
        * @return true если парсинг успешен
        */
        static bool parse(int argc, char* argv[], Config & cfg);
};

/**
 * @brief Проверяет корректность конфигурации
 */
class ConfigValidator {
    public:

        /**
        * @brief Проверяет все пути в конфигурации
        * 
        * @param cfg Конфигурация
        * @return true если все пути валидны
        */
        static bool validate(const Config & cfg);

    private:

        /**
        * @brief Проверяет, что путь существует и является директорией
        */
        static bool check_directory(const std::filesystem::path & directory);

        /**
        * @brief Проверяет, что путь существует и является обычным файлом
        */
        static bool check_file(const std::filesystem::path & file);


        /**
        * @brief Проверяет существование пути
        */
        static bool check_exists(const std::filesystem::path & path);
};