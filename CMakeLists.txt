cmake_minimum_required(VERSION 3.10)

project(myTask)

add_executable(agent
    src/main.cpp
    src/app/agent.cpp
    src/config/config.cpp
    src/crypto/hasher.cpp
    src/io/report_writer.cpp
    src/io/values_reader.cpp
    src/scan/directory_scanner.cpp
    src/scan/file_processor.cpp

)

find_package(OpenSSL REQUIRED)

target_link_libraries(agent PRIVATE OpenSSL::Crypto)