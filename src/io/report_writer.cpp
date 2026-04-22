#include "report_writer.h"
#include <filesystem>
#include <fstream>
#include <mutex>


ReportWriter::ReportWriter(
    const std::filesystem::path& white,
    const std::filesystem::path& black,
    const std::filesystem::path& anomaly)
{
    white_out.open(white);
    black_out.open(black);
    anomaly_out.open(anomaly);

    if (!white_out) {
        throw std::runtime_error("Failed to open output file: " + white.string());
    }
    if (!black_out) {
        throw std::runtime_error("Failed to open output file: " + black.string());
    }
    if (!anomaly_out) {
        throw std::runtime_error("Failed to open output file: " + anomaly.string());
    }
}

void ReportWriter::write(const Result& result) {
    std::lock_guard<std::mutex> lock(m);
    
    switch (result.type) {
        case Result::Type::White:
            white_out << result.file.string() << '\n';
            break;
        case Result::Type::Black:
            black_out << result.file.string() << '\n';
            break;
        case Result::Type::Anomaly:
            anomaly_out << result.file.string() << '\n';
            break;
        case Result::Type::Ignored:
            break;
    }
}