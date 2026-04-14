#include "config.h"


// ConfigParser

bool ConfigParser::parse(int argc, char* argv[], Config & cfg) {
    if (argc != 5) {
        std::cerr << "Incorrect number of arguments. Use: \"./agent <directory> <white.txt> <black.txt> <ext.txt>\"\n";
        return false;
    }

    cfg.scan_directory = argv[1];
    cfg.white_list_file = argv[2];
    cfg.black_list_file = argv[3];
    cfg.extensions_file = argv[4];

    return true;
}


// ConfigValidator

bool ConfigValidator::validate(const Config & cfg) {
    bool okay = true;

    if (!check_directory(cfg.scan_directory)) okay = false;
    if (!check_file(cfg.white_list_file)) okay = false;
    if (!check_file(cfg.black_list_file)) okay = false;
    if (!check_file(cfg.extensions_file)) okay = false;

    return okay;
}
bool ConfigValidator::check_directory(const std::filesystem::path & directory) {
    if (!check_exists(directory)) return false;
    
    if (!std::filesystem::is_directory(directory)) {
        std::cerr << "Not a directory: " << directory << std::endl;
        return false;
    }
    return true;
}

bool ConfigValidator::check_file(const std::filesystem::path & file) {
    if (!check_exists(file)) return false;
    
    if (!std::filesystem::is_regular_file(file)) {
        std::cerr << "Not a regular file: " << file << std::endl;
        return false;
    }

    return true;
}


bool ConfigValidator::check_exists(const std::filesystem::path & path) {
    if (!std::filesystem::exists(path)) {
        std::cerr << "Path not found: " << path << std::endl;
        return false;
    }
    return true;
}