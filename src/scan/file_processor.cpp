#include "file_processor.h"
#include "../crypto/hasher.h"
#include "../io/report_writer.h"


FileProcessor::FileProcessor(const std::unordered_set<std::string>& white,
                const std::unordered_set<std::string>& black,
                const std::unordered_set<std::string>& extensions,
                ReportWriter& wrt)
    : white(white), black(black), extensions(extensions), writer(wrt) {}

void FileProcessor::process(const std::filesystem::path& file) {
    if (!check_extension(file)) return;

    auto hash = md5_file(file);

    if (white.find(hash) != white.end())
        writer.write(ReportWriter::Type::White, file);
    else if (black.find(hash) != black.end())
        writer.write(ReportWriter::Type::Black, file);
    else
        writer.write(ReportWriter::Type::Anomaly, file);
}

bool FileProcessor::check_extension(const std::filesystem::path& file) {
    return extensions.find(file.extension().string()) != extensions.end();
}