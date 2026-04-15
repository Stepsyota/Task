#pragma once

#include <filesystem>


/**
 * @brief Парсит, валидирует и хранит пути, переданные через аргументы командной строки
 */
class Config {
    public:
        Config(int argc, char* argv[]);

        /**
        * @brief Возвращает путь директории для сканирования
        * @return path
        */
        const std::filesystem::path & get_scan_directory() const;

        /**
        * @brief Возвращает путь файла белого списка
        * @return path
        */
        const std::filesystem::path & get_white_list_file() const;

        /**
        * @brief Возвращает путь файла черного списка
        * @return path
        */
        const std::filesystem::path & get_black_list_file() const;

        /**
        * @brief Возвращает путь файла расширений
        * @return path
        */
        const std::filesystem::path & get_extensions_file() const;

    private:
        /**
        * @brief Проверяет корректность конфигурации.
        *
        * Убеждается, что все пути существуют и имеют корректный тип
        * (директория или файл).
        *
        * @throws std::runtime_error если конфигурация некорректна
        */
        void validate() const;

        /**
        * @brief Проверяет, что путь существует и является директорией.
        *
        * @throws std::runtime_error если путь не существует или не является директорией
        */
        static void check_directory(const std::filesystem::path & directory);

        /**
        * @brief Проверяет, что путь существует и является обычным файлом.
        *
        * @throws std::runtime_error если путь не существует или не является файлом
        */
        static void check_file(const std::filesystem::path & file);

        /**
        * @brief Проверяет существование пути в файловой системе.
        *
        * @throws std::runtime_error если путь не найден
        */
        static void check_exists(const std::filesystem::path & path);

        std::filesystem::path scan_directory;   //< Директория для сканирования
        std::filesystem::path white_list_file;  //< Файл белого списка
        std::filesystem::path black_list_file;  //< Файл черного списка
        std::filesystem::path extensions_file;  //< Файл расширений
};