#pragma once

#include <string>
#include <filesystem>
#include "version.h"



/**
* @brief Модуль сбора и записи общей информации о проекте.
*
* InfoWriter отвечает за:
* - определение версии проекта
* - определение операционной системы
* - обнаружение CMS WordPress и её версии
* - сохранение собранной информации в файл
*/
class InfoWriter {
    public:
        /**
        * @brief Структура, содержащая информацию о проекте.
        */
        struct Info {
            std::string project_version;    ///< Версия проекта
            std::string os;                 ///< Операционная система
            bool is_wordpress;              ///< Является ли проект WordPress
            std::string wp_version;         ///< Версия WordPress (если применимо)
        };

        /**
        * @brief Собирает информацию о проекте в указанной директории.
        *
        * Выполняет:
        * - определение версии приложения
        * - определение ОС
        * - проверку, является ли проект WordPress
        * - извлечение версии WordPress (если применимо)
        *
        * @param root Корневая директория проекта
        * @return экземпляр Info с собранной информацией
        */
        static Info collect(const std::filesystem::path& root);

        /**
        * @brief Записывает информацию о проекте в файл.
        *
        * Создаёт файл `info.txt` в указанной директории и записывает:
        * - версию проекта
        * - операционную систему
        * - информацию о CMS (если обнаружена)
        *
        * @param info Экзмепляр Info с информацией о проекте
        * @param path Директория для записи файла (по умолчанию текущая)
        */
        static void write(const Info& info, const std::filesystem::path& path = "");
};

