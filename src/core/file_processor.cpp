#include "file_processor.h"
#include "../crypto/hasher.h"


FileProcessor::FileProcessor(const std::unordered_set<std::string>& white,
                const std::unordered_set<std::string>& black,
                const std::unordered_set<std::string>& extensions)
    : white(white), black(black), extensions(extensions) {}

Result FileProcessor::process(const std::filesystem::path& file) {
    if (!check_extension(file)) {
        return {Result::Type::Ignored, file};
    }

    auto hash = md5_file(file);

    if (white.contains(hash))
        return {Result::Type::White, file};
    else if (black.contains(hash))
        return {Result::Type::Black, file};

    return {Result::Type::Anomaly, file};
}

bool FileProcessor::check_extension(const std::filesystem::path& file) {
    return extensions.contains(file.extension().string());
}