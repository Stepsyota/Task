#pragma once

#include <filesystem>
#include <fstream>


/**
* @brief Записывает результаты сканирования файла в разные категории
*/
class ScanReportWriter {
    public:

        /**
        * @brief Открывает потоки файлов для записи результатов
        * 
        * @param white путь к файлу output_white.txt
        * @param black путь к файлу output_black.txt
        * @param anomaly путь к файлу output_anomaly.txt
        */
        ScanReportWriter(const std::filesystem::path& white,
                    const std::filesystem::path& black,
                    const std::filesystem::path& anomaly);
        

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