#pragma once

#include <string>
#include <filesystem>
#include "version.h"


class InfoWriter {
    public:
    
    struct Info {
        std::string agent_version;
        std::string os;
        bool is_wordpress;
        std::string wp_version;
    };

    static Info collect(const std::filesystem::path& root);
    static void write(const Info& info, const std::filesystem::path& path = "");
};

