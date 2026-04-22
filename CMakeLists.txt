cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(agent VERSION 1.0.0 LANGUAGES CXX)

add_executable(agent
    src/main.cpp
    src/app/agent.cpp
    src/config/config.cpp
    src/crypto/hasher.cpp
    src/io/report_writer.cpp
    src/io/values_reader.cpp
    src/io/info_writer.cpp
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


# CPack

install(TARGETS agent
    RUNTIME DESTINATION bin
)

set(CPACK_GENERATOR "DEB;RPM")

set(CPACK_PACKAGE_NAME "agent")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "stepsyota@gmail.com")

set(CPACK_PACKAGE_DESCRIPTION "File analysis agent")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Stepan Good")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libssl3")

include(CPack)