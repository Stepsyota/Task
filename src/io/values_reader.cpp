#include "values_reader.h"
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

std::unordered_set<std::string> ValuesReader::load_hashes_to_set(const std::filesystem::path& path) {
    std::unordered_set<std::string> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
            result.insert(token);
        }
    }

    return result;
}

std::unordered_set<std::string> ValuesReader::load_extensions_to_set(const std::filesystem::path& path) {
    std::unordered_set<std::string> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        while (iss >> token) {
            if (!token.empty() && token[0] != '.'){
                token = "." + token;
            }
            std::transform(token.begin(), token.end(), token.begin(),
                [](unsigned char c){ return std::tolower(c); });
            result.insert(token);
        }
    }

    return result;
}