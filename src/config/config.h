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

        /**
        * @brief Возвращает путь к выходному файлу для white хэшей
        * @return path
        */
        const std::filesystem::path & get_white_output_file() const;

        /**
        * @brief Возвращает путь к выходному файлу для black хэшей
        * @return path
        */
        const std::filesystem::path & get_black_output_file() const;

        /**
        * @brief Возвращает путь к выходному файлу для неизвестных хэшей
        * @return path
        */
        const std::filesystem::path & get_anomaly_output_file() const;

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

        std::filesystem::path white_output_file = "output_white.txt";       //< Выходной файл white (временно, может быть переопределенно в будущем)
        std::filesystem::path black_output_file = "output_black.txt";       //< Выходной файл black (временно, может быть переопределенно в будущем)
        std::filesystem::path anomaly_output_file = "output_anomaly.txt";   //< Выходной файл anomaly (временно, может быть переопределенно в будущем)
};