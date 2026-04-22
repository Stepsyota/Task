#include "agent.h"
#include "../scan/directory_scanner.h"
#include "../core/file_processor.h"
#include "../io/values_reader.h"
#include "../io/info_writer.h"

#include <vector>
#include <future>

Agent::Agent(Config cfg) : config(cfg), 
    writer(cfg.get_white_output_file(),
        cfg.get_black_output_file(),
        cfg.get_anomaly_output_file()) {
            
        white_hash_set = ValuesReader::load_hashes_to_set(cfg.get_white_list_file());
        black_hash_set = ValuesReader::load_hashes_to_set(cfg.get_black_list_file());
        extensions_set = ValuesReader::load_extensions_to_set(cfg.get_extensions_file());
    }

void Agent::run() {
    auto info = InfoWriter::collect(config.get_scan_directory());
    InfoWriter::write(info);

    FileProcessor processor(
        white_hash_set,
        black_hash_set,
        extensions_set
    );

    std::vector<std::future<void>> tasks;

    DirectoryScanner scanner;

    scanner.scan(config.get_scan_directory(), [&](const std::filesystem::path& file) {

        tasks.push_back(std::async(std::launch::async, [&, file]() {
            auto result = processor.process(file);
            writer.write(result);
        }));

    });

    for (auto& t : tasks) {
        t.get();
    }
}