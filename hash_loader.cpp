#include "hash_loader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


std::unordered_set<std::string> HashLoader::load_words_to_set(const std::filesystem::path& path) {
    std::unordered_set<std::string> result;

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << "\n";
        return result;
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