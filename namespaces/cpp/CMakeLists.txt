# generated/ belongs to kibo; src/ is written by hand.
#
# The six files in src/ have no main(): each exercises one facet of the generated surface --
# fields, codec, json, an attachment read, a pool. Putting them in the library makes them
# compile *and* link, which a plain `-fsyntax-only` would not check.
file(GLOB TOPOLOGY_HEADERS generated/*.hpp)
file(GLOB TOPOLOGY_SOURCES generated/*.cpp)
list(FILTER TOPOLOGY_SOURCES EXCLUDE REGEX "_test_app\\.cpp$")
file(GLOB TOPOLOGY_CONSUMERS src/*.cpp)

add_library(topology STATIC
    ${TOPOLOGY_HEADERS} ${TOPOLOGY_SOURCES} ${TOPOLOGY_CONSUMERS})
target_include_directories(topology PUBLIC generated)
target_link_libraries(topology PUBLIC viper)

add_executable(topology_test generated/topology_test_app.cpp)
target_link_libraries(topology_test topology cli11)
