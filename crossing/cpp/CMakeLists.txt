# generated/ belongs to kibo. This site has no src/: what it tests is references that
# cross a namespace inside a composite -- a `map<Core::Grade, Parts::Colour>`, a
# `variant<Core::Colour, Parts::Colour>`. The compiler is the judge.
file(GLOB CROSSING_HEADERS generated/*.hpp)
file(GLOB CROSSING_SOURCES generated/*.cpp)
list(FILTER CROSSING_SOURCES EXCLUDE REGEX "_test_app\\.cpp$")

add_library(crossing STATIC
    ${CROSSING_HEADERS} ${CROSSING_SOURCES})
target_include_directories(crossing PUBLIC generated)
target_link_libraries(crossing PUBLIC viper)

add_executable(crossing_test generated/crossing_test_app.cpp)
target_link_libraries(crossing_test crossing cli11)
