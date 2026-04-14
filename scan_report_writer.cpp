#include "scan_report_writer.h"
#include <filesystem>
#include <fstream>


ScanReportWriter::ScanReportWriter(const std::filesystem::path& white,
            const std::filesystem::path& black,
            const std::filesystem::path& anomaly)
        : white_out(white),
        black_out(black),
        anomaly_out(anomaly)
    {
        if (!white_out.is_open() || !black_out.is_open() || !anomaly_out.is_open()) {
            throw std::runtime_error("Failed to open output files");
        }
    }

void ScanReportWriter::write(Type type, const std::filesystem::path& file) {
    std::ofstream* out = nullptr;

    switch (type) {
        case Type::White:   out = &white_out; break;
        case Type::Black:   out = &black_out; break;
        case Type::Anomaly: out = &anomaly_out; break;
        default: return;
    }

    if (out && out->is_open()) {
        *out << file << "\n";
    }
}