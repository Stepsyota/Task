#pragma once

#include <filesystem>


/**
 * @brief Компонент обхода файловой системы.
 *
 * DirectoryScanner реализует этап получения входных данных для pipeline обработки.
 * Его задача — рекурсивно обойти директорию и передать все файлы на обработку
 * через callback-функцию.
 *
 * Класс не выполняет обработку файлов и не хранит состояние.
 */
class DirectoryScanner {
    public:
        /**
        * @brief Рекурсивно обходит файловую систему и передаёт файлы в обработчик.
        *
        * Выполняет обход директории root и для каждого регулярного файла вызывает callback.
        * Нерелевантные сущности (директории, ссылки и т.п.) игнорируются.
        *
        * Реализует streaming-подход без накопления списка файлов в памяти.
        *
        * @tparam Callback Callable объект, принимающий std::filesystem::path
        * @param root Корневая директория для обхода
        * @param cb Функция обработки каждого найденного файла
        */
        template <typename Callback>
        void scan(const std::filesystem::path& root, Callback cb) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {

                if (entry.is_regular_file()) {
                    cb(entry.path());
                }
            }
        }
};