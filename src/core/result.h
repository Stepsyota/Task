#pragma once

#include <filesystem>


/**
 * @brief Результат классификации файла в pipeline анализа.
 *
 * Result является единицей передачи данных между стадиями обработки:
 * FileProcessor → Agent → ReportWriter.
 *
 * Он описывает итоговую категорию файла и его путь в файловой системе.
 */
struct Result {
    /**
    * @brief Тип классификации файла.
    *
    * Определяет результат анализа содержимого файла:
    * - White   : файл найден в whitelist (доверенный)
    * - Black   : файл найден в blacklist (подозрительный/запрещённый)
    * - Anomaly : файл не найден ни в одном списке (неизвестный)
    * - Ignored : файл не был обработан (например, неподходящее расширение)
    */
    enum class Type { White, Black, Anomaly, Ignored };

    Type type = Type::Ignored;  ///< Результат классификации файла
    std::filesystem::path file; ///< Путь к обработанному файлу
};