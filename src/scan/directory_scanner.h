#pragma once

#include "file_processor.h"
#include "../io/report_writer.h"

#include <filesystem>
#include <unordered_set>

class DirectoryScanner {
    public:
        static void scan(const std::filesystem::path& root, FileProcessor& processor);
};