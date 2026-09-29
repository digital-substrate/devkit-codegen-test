# generated/ est à kibo. Ce site n'a pas de src/ : ce qu'il éprouve, ce sont les références
# qui traversent un namespace à l'intérieur d'un composite -- un `map<Core::Grade,
# Parts::Colour>`, un `variant<Core::Colour, Parts::Colour>`. Le compilateur est le juge.
file(GLOB CROSSING_HEADERS generated/*.hpp)
file(GLOB CROSSING_SOURCES generated/*.cpp)
list(FILTER CROSSING_SOURCES EXCLUDE REGEX "_TestApp\\.cpp$")

add_library(crossing STATIC
    ${CROSSING_HEADERS} ${CROSSING_SOURCES})
target_include_directories(crossing PUBLIC generated)
target_link_libraries(crossing PUBLIC viper)

add_executable(crossing_test generated/Crossing_TestApp.cpp)
target_link_libraries(crossing_test crossing cli11)
