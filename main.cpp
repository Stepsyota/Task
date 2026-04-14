#include <iostream>
#include "config.h"

int main(int argc, char* argv[]) {
    Config cfg;

    if (!ConfigParser::parse(argc, argv,cfg)) {
        return 1;
    }

    if (!ConfigValidator::validate(cfg)) {
        return 1;
    }


    std::cout << cfg.scan_directory << std::endl;
    std::cout << cfg.white_list_file << std::endl;
    std::cout << cfg.black_list_file << std::endl;
    std::cout << cfg.extensions_file << std::endl;

    return 0;
}