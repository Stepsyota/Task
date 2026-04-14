#pragma once

#include <iostream>
#include <filesystem>

struct Config {
    std::filesystem::path scan_directory;
    std::filesystem::path white_list_file;
    std::filesystem::path black_list_file;
    std::filesystem::path extensions_file;
};

class ConfigParser {
    public:
        static bool parse(int argc, char* argv[], Config & cfg);
};

class ConfigValidator {
    public:
        static bool validate(const Config & cfg);

    private:
        static bool check_directory(const std::filesystem::path & directory);

        static bool check_file(const std::filesystem::path & file);

        static bool check_exists(const std::filesystem::path & path);
};