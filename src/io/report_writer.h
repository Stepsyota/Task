#pragma once

#include <filesystem>
#include <fstream>
#include "../core/result.h"


/**
 * @brief Компонент записи результатов анализа файлов.
 *
 * ReportWriter является конечной стадией pipeline обработки файлов.
 * Он принимает результаты классификации и распределяет их по отдельным файлам:
 * - whitelist результаты
 * - blacklist результаты
 * - аномальные файлы
 */
class ReportWriter {
    public:
        /**
        * @brief Открывает выходные файлы для записи результатов анализа.
        *
        * Инициализирует файловые потоки для каждой категории результата:
        * - white
        * - black
        * - anomaly
        *
        * @throws std::runtime_error если невозможно открыть один из выходных файлов
        */
        ReportWriter(const std::filesystem::path& white_out, const std::filesystem::path& black_out, const std::filesystem::path& anomaly_out);


        /**
        * @brief Записывает результат анализа в соответствующий выходной файл.
        *
        * Выполняет маршрутизацию результата в зависимости от его типа:
        * - White   → файл whitelist
        * - Black   → файл blacklist
        * - Anomaly → файл неизвестных/подозрительных файлов
        * - Ignored → не записывается
        *
        * @param result Результат классификации файла
        */
        void write(const Result& result);

    private:
        std::ofstream white_out;    ///< Поток файла для whitelist результатов
        std::ofstream black_out;    ///< Поток файла для blacklist результатов
        std::ofstream anomaly_out;  ///< Поток файла для аномальных файлов
};