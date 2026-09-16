# generated/ est à kibo ; src/ est écrit à la main.
#
# LES SIX FICHIERS DE src/ N'ONT PAS DE main() : chacun éprouve une facette de la surface
# générée -- les champs, le codec, le json, un attachment lu, un pool. Les mettre dans la
# bibliothèque les fait compiler *et* lier, ce qu'un simple `-fsyntax-only` ne dirait pas.
file(GLOB TOPOLOGY_HEADERS generated/*.hpp)
file(GLOB TOPOLOGY_SOURCES generated/*.cpp)
list(FILTER TOPOLOGY_SOURCES EXCLUDE REGEX "_TestApp\\.cpp$")
file(GLOB TOPOLOGY_CONSUMERS src/*.cpp)

# Ce que le runtime devrait porter et ne porte pas encore -- le pendant C++ du `_codegen`
# embarqué en Python et TypeScript. Dette, pas choix.
set(PROPOSED ${CMAKE_CURRENT_SOURCE_DIR}/../../runtime-proposed/cpp)
file(GLOB PROPOSED_SOURCES ${PROPOSED}/*.cpp)
file(GLOB PROPOSED_HEADERS ${PROPOSED}/*.hpp)

add_library(topology STATIC
    ${TOPOLOGY_HEADERS} ${TOPOLOGY_SOURCES} ${TOPOLOGY_CONSUMERS}
    ${PROPOSED_HEADERS} ${PROPOSED_SOURCES})
target_include_directories(topology PUBLIC generated ${PROPOSED})
target_link_libraries(topology PUBLIC viper)

add_executable(topology_test generated/Topology_TestApp.cpp)
target_link_libraries(topology_test topology cli11)
