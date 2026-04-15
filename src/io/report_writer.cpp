#include "report_writer.h"
#include <filesystem>
#include <fstream>


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
        throw std::runtime_error("Failed to open output file: " + white.string());
    }
    if (!anomaly_out) {
        throw std::runtime_error("Failed to open output file: " + white.string());
    }
}

void ReportWriter::write(Type type, const std::filesystem::path& file) {
    switch (type) {
        case Type::White:
            white_out << file.string() << '\n';
            break;
        case Type::Black:
            black_out << file.string() << '\n';
            break;
        case Type::Anomaly:
            anomaly_out << file.string() << '\n';
            break;
    }
}