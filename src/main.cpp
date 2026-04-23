#include <exception>
#include <iostream>
#include "config/config.h"
#include "crypto/hasher.h"
#include "app/agent.h"
#include "io/report_writer.h"

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    
    try {
        Config cfg(argc, argv);

        Agent agent(cfg);
        agent.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    return 0;
}