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

# Every site depends on Kibo-generated sources existing at configure time.
# Render a site's C++ from its kibo.toml BEFORE invoking cmake:
#
#   cd features && python3 ../../kibo-project/kibo_project.py generate --target cpp
#
# or render every site, and test it, with `python3 check.py`.
#
# Then from the repo root:
#
#   mkdir build && cd build && cmake .. && cmake --build . -j
#
# Subdirs are skipped (with a notice) when the generated sources are
# missing, so a fresh clone configures cleanly.

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/features/cpp/generated)
    add_subdirectory(features/cpp)
else()
    message(STATUS "features/ skipped: run 'cd features && python3 ../../kibo-project/kibo_project.py generate --target cpp' first")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/service/cpp/generated)
    add_subdirectory(service/cpp)
else()
    message(STATUS "service/ skipped: run 'cd service && python3 ../../kibo-project/kibo_project.py generate --target cpp' first")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/namespaces/cpp/generated)
    add_subdirectory(namespaces/cpp)
else()
    message(STATUS "namespaces/ skipped: run 'cd namespaces && python3 ../../kibo-project/kibo_project.py generate --target cpp' first")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/crossing/cpp/generated)
    add_subdirectory(crossing/cpp)
else()
    message(STATUS "crossing/ skipped: run 'cd crossing && python3 ../../kibo-project/kibo_project.py generate --target cpp' first")
endif()

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/compat-1.2/cpp/generated)
    add_subdirectory(compat-1.2/cpp)
else()
    message(STATUS "compat-1.2/ skipped: run 'cd compat-1.2 && python3 ../../kibo-project/kibo_project.py generate --target cpp' first")
endif()
