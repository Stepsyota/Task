#pragma once

#include "../config/config.h"
#include "../io/report_writer.h"
#include <unordered_set>


class Agent {
public:
    Agent(Config cfg);

    void run();

private:
    Config config;
    ReportWriter writer;

    std::unordered_set<std::string> white_hash_set;
    std::unordered_set<std::string> black_hash_set;
    std::unordered_set<std::string> extensions_set;

    void load_sets();
};