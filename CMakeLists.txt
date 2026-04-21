cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(agent VERSION 1.0.0 LANGUAGES CXX)

add_executable(agent
    src/main.cpp
    src/app/agent.cpp
    src/config/config.cpp
    src/crypto/hasher.cpp
    src/io/report_writer.cpp
    src/io/values_reader.cpp
    src/io/info_writer.cpp
    src/scan/directory_scanner.cpp
    src/core/file_processor.cpp
)

find_package(OpenSSL REQUIRED)

target_link_libraries(agent PRIVATE OpenSSL::Crypto)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
    @ONLY
)

target_include_directories(agent PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_BINARY_DIR}/generated
)