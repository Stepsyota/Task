#include "agent.h"
#include "../scan/directory_scanner.h"
#include "../core/file_processor.h"
#include "../io/values_reader.h"
#include "../io/info_writer.h"
#include <iostream>


Agent::Agent(Config cfg) : config(cfg), 
    writer(cfg.get_white_output_file(),
        cfg.get_black_output_file(),
        cfg.get_anomaly_output_file()) {
            
        white_hash_set = ValuesReader::load_hashes_to_set(cfg.get_white_list_file());
        black_hash_set = ValuesReader::load_hashes_to_set(cfg.get_black_list_file());
        extensions_set = ValuesReader::load_extensions_to_set(cfg.get_extensions_file());

        // Устранить неоднозначность: хэши, присутствующие в black, не должны оставаться в white.
        // Это делает классификацию детерминированной и устраняет "перетягивание" результатов.
        size_t removed_from_white = 0;
        for (const auto& h : black_hash_set) {
            removed_from_white += white_hash_set.erase(h);
        }

        if (removed_from_white != 0) {
            std::cerr << "Warning: removed " << removed_from_white
                      << " hashes from white list because they are also present in black list.\n";
        }
    }

void Agent::run() {
    auto info = InfoWriter::collect(config.get_scan_directory());
    InfoWriter::write(info);

    FileProcessor processor(
        white_hash_set,
        black_hash_set,
        extensions_set
    );

    DirectoryScanner scanner;
    scanner.scan(config.get_scan_directory(), [&](const std::filesystem::path & file) {
        const auto result = processor.process(file);
        writer.write(result);
    });
}
