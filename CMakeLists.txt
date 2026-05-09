cmake_minimum_required(VERSION 3.16)

project(devkit-codegen-test LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif ()

if (LINUX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# Build viper + third_parties from the sibling com.digitalsubstrate.viper
# checkout. Defines targets: sqlite, json, hash, antlr4, cli11, viper.
include(lib.cmake)

# features/ and service/ both depend on Kibo-generated sources existing
# at configure time. Run their generate.py with -c BEFORE invoking cmake:
#
#   cd features && python3 generate.py all.dsm -c -p
#   cd ../service && python3 generate.py -c -p
#
# Then from the repo root:
#
#   mkdir build && cd build && cmake .. && cmake --build . -j
#
# Subdirs are skipped (with a notice) when the generated sources are
# missing, so a fresh clone configures cleanly.

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/features/Features)
    add_subdirectory(features)
else()
    message(STATUS "features/ skipped: run 'cd features && python3 generate.py all.dsm -c' first")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/service/Service)
    add_subdirectory(service)
else()
    message(STATUS "service/ skipped: run 'cd service && python3 generate.py -c' first")
endif()
