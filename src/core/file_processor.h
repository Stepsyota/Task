#pragma once

#include <unordered_set>
#include <filesystem>
#include "result.h"


/**
 * @brief Компонент классификации файлов по содержимому.
 *
 * FileProcessor является стадией обработки в pipeline анализа файловой системы.
 * Его задача — преобразовать входной файл в результат классификации (Result).
 *
 * Классификация выполняется на основе:
 * - хэша файла (MD5)
 * - whitelist / blacklist наборов
 * - списка разрешённых расширений
 *
 */
class FileProcessor {
    public:
        /**
        * @brief Инициализирует процессор набором справочных данных.
        *
        * FileProcessor не владеет переданными наборами данных,
        * а использует их в read-only режиме.
        *
        * Эти данные используются для классификации файлов в методе process().
        *
        * @param white Набор разрешённых (trusted) хэшей файлов
        * @param black Набор запрещённых (suspicious/malicious) хэшей файлов
        * @param extensions Набор допустимых расширений файлов
        */
        FileProcessor(const std::unordered_set<std::string>& white,
                    const std::unordered_set<std::string>& black,
                    const std::unordered_set<std::string>& extensions);


        /**
        * @brief Выполняет классификацию файла.
        *
        * Алгоритм работы:
        * 1. Проверка расширения файла
        * 2. Вычисление MD5-хэша содержимого
        * 3. Сравнение хэша с whitelist и blacklist
        * 4. Формирование результата классификации
        *
        * Возможные типы результата:
        * - White   : файл присутствует в whitelist
        * - Black   : файл присутствует в blacklist
        * - Anomaly : файл не найден ни в одном списке
        * - Ignored : файл не проходит фильтр по расширению
        *
        * @param file Путь к обрабатываемому файлу
        * @return Result с типом классификации и путём файла
        */
        Result process(const std::filesystem::path& file);
    private:
        /**
        * @brief Проверяет, разрешено ли расширение файла для обработки.
        *
        * @param file Путь к файлу
        * @return true если расширение входит в список разрешённых
        */
        bool check_extension(const std::filesystem::path& file);

        const std::unordered_set<std::string>& white;       ////< Read-only whitelist хэшей
        const std::unordered_set<std::string>& black;       ////< Read-only blacklist хэшей
        const std::unordered_set<std::string>& extensions;  ////< Read-only множество расширений
};