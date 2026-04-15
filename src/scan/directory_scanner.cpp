#include "directory_scanner.h"

#include "file_processor.h"
#include <filesystem>


void DirectoryScanner::scan(const std::filesystem::path& root, FileProcessor & processor) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {

        if (!entry.is_regular_file())
            continue;

        processor.process(entry);
    }
}