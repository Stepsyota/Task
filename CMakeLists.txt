cmake_minimum_required(VERSION 3.10)

project(myTask)

add_executable(agent
    main.cpp
    config.cpp
    hash_loader.cpp
    scan_report_writer.cpp
)