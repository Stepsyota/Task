#include "agent.h"
#include "../scan/directory_scanner.h"
#include "../core/file_processor.h"
#include "../io/values_reader.h"


Agent::Agent(Config cfg) : config(cfg), writer("output_white.txt", "output_black.txt", "output_anomaly.txt"){}

void Agent::run() {
    load_sets();

    FileProcessor processor(white_hash_set, black_hash_set, extensions_set, writer);
    DirectoryScanner::scan(config.get_scan_directory(), processor);
}

void Agent::load_sets() {
    white_hash_set = ValuesReader::load_hashes_to_set(config.get_white_list_file());
    black_hash_set = ValuesReader::load_hashes_to_set(config.get_black_list_file());
    extensions_set = ValuesReader::load_extensions_to_set(config.get_extensions_file());
}