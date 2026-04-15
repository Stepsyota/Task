#pragma once

#include <filesystem>
#include <fstream>


/**
* @brief Записывает результаты сканирования файла в разные категории
*/
class ReportWriter {
    public:

        /**
        * @brief Открывает потоки файлов для записи результатов
        */
        ReportWriter(const std::filesystem::path& white_out, const std::filesystem::path& black_out, const std::filesystem::path& anomaly_out);

        /**
        * @brief Категория результата сканирования файла
        * 
        */
        enum class Type {
            White,
            Black,
            Anomaly
        };

        /**
        * @brief Записывает путь в соответствующий категории тип файла
        * 
        * @param type категория результата
        * @param file путь файла, который будет записан
        */
        void write(Type type, const std::filesystem::path& file);

    private:
        std::ofstream white_out;    //< Поток файла output_white.txt
        std::ofstream black_out;    //< Поток файла output_black.txt
        std::ofstream anomaly_out;  //< Поток файла output_anomaly.txt
};