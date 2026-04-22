#include "info_writer.h"
#include <filesystem>
#include <fstream>


/**
* @brief Определяет текущую операционную систему.
*
* Использует макросы компилятора для определения платформы.
*
* @return Название ОС (Windows, Linux, macOS или Unknown)
*/
static std::string detect_os() {
#ifdef _WIN32
    return "Windows";
#elif __linux__
    return "Linux";
#elif __APPLE__
    return "macOS";
#else
    return "Unknown";
#endif
}


/**
* @brief Возвращает версию проекта.
*
* Значение берётся из макроса PROJECT_VERSION.
*
* @return Строка с версией проекта
*/
static std::string detect_project_version() {
    return std::string(PROJECT_VERSION);
}

/**
* @brief Проверяет, является ли директория WordPress-проектом.
*
* Проверяет наличие стандартных директорий:
* - wp-admin
* - wp-content
* - wp-includes
*
* @param root Корневая директория проекта
* @return true если это WordPress, иначе false
*/
static bool is_wordpress(const std::filesystem::path& root) {
    return std::filesystem::exists(root / "wp-admin") &&
        std::filesystem::exists(root / "wp-content") &&
        std::filesystem::exists(root / "wp-includes");
}

/**
* @brief Извлекает версию WordPress из файла version.php.
*
* Парсит файл wp-includes/version.php и ищет переменную $wp_version.
*
* @param root Корневая директория проекта
* @return Версия WordPress или "Unknown version" при ошибке
*/
static std::string get_wp_version(const std::filesystem::path& root) {
    std::ifstream file(root / "wp-includes" / "version.php");
    if (!file)
        return "Unknown version";

    std::string line;

    while (std::getline(file, line)) {
        if (line.find("$wp_version") == std::string::npos)
            continue;

        auto first = line.find_first_of("'/");
        auto second = line.find_first_of("'\"", first + 1);

        if (first != std::string::npos && second != std::string::npos) {
            return line.substr(first + 1, second - first - 1);
        }
    }

    return "Unknown version";
}

InfoWriter::Info InfoWriter::collect(const std::filesystem::path& root) {
    InfoWriter::Info info;

    info.project_version = detect_project_version();
    info.os = detect_os();

    info.is_wordpress = is_wordpress(root);
    if (info.is_wordpress) {
        info.wp_version = get_wp_version(root);
    }
    else {
        info.wp_version = "N/A";
    }
    return info;
}

void InfoWriter::write(const InfoWriter::Info& info, const std::filesystem::path& path) {
    std::ofstream out(path / "info.txt");

    out << "Project version: " << info.project_version << '\n';
    out << "OS: " << info.os << '\n';

    if (info.is_wordpress) {
        out << "CMS: WordPress\n";
        out << "WordPress version: " << info.wp_version << '\n';
    } else {
        out << "CMS: unknown\n";
    }
}
