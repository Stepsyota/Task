#include "config.h"
#include <stdexcept>


Config::Config(int argc, char* argv[]) {
    if (argc != 5) {
        throw std::runtime_error("Incorrect number of arguments. Use: \"./agent <directory> <white.txt> <black.txt> <ext.txt>\"\n");
    }

    scan_directory = argv[1];
    white_list_file = argv[2];
    black_list_file = argv[3];
    extensions_file = argv[4];

    validate();
}


const std::filesystem::path & Config::get_scan_directory() const {
    return scan_directory;
}

const std::filesystem::path & Config::get_white_list_file() const {
    return white_list_file;
}

const std::filesystem::path & Config::get_black_list_file() const {
    return black_list_file;
}

const std::filesystem::path & Config::get_extensions_file() const {
    return extensions_file;
}

const std::filesystem::path & Config::get_white_output_file() const {
    return white_output_file;
}

const std::filesystem::path & Config::get_black_output_file() const {
    return black_output_file;
}

const std::filesystem::path & Config::get_anomaly_output_file() const {
    return anomaly_output_file;
}

void Config::validate() const{
    check_directory(scan_directory);
    check_file(white_list_file);
    check_file(black_list_file);
    check_file(extensions_file);
}

void Config::check_directory(const std::filesystem::path & directory) {
    check_exists(directory);
    
    if (!std::filesystem::is_directory(directory)) {
        throw std::runtime_error("Not a directory: " + directory.string());
    }
}

void Config::check_file(const std::filesystem::path & file) {
    check_exists(file);
    
    if (!std::filesystem::is_regular_file(file)) {
        throw std::runtime_error("Not a regular file: " + file.string());
    }
}


void Config::check_exists(const std::filesystem::path & path) {
    if (!std::filesystem::exists(path)) {
        throw std::runtime_error("Path not found: " + path.string());
    }
}