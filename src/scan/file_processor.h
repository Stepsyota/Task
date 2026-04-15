#pragma once

#include "../io/report_writer.h"
#include <unordered_set>
#include <filesystem>


class FileProcessor {
public:
    FileProcessor(const std::unordered_set<std::string>& white,
                  const std::unordered_set<std::string>& black,
                  const std::unordered_set<std::string>& extensions,
                  ReportWriter& writer);

    void process(const std::filesystem::path& file);
private:
    bool check_extension(const std::filesystem::path& file);

private:
    const std::unordered_set<std::string>& white;
    const std::unordered_set<std::string>& black;
    const std::unordered_set<std::string>& extensions;

    ReportWriter& writer;
};