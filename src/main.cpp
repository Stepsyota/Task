#include <exception>
#include <iostream>
#include "config/config.h"
#include "crypto/hasher.h"
#include "app/agent.h"
#include "io/report_writer.h"

int main(int argc, char* argv[]) {
    try {
        Config cfg(argc, argv);

        Agent agent(cfg);
        agent.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}