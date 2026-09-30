# Everything kibo writes is in generated/, including the test program, which comes from the
# TestApp template. It has a main(), so it is excluded from the library explicitly.
file(GLOB FEATURES_HEADERS generated/*.hpp)
file(GLOB FEATURES_SOURCES generated/*.cpp)
list(FILTER FEATURES_SOURCES EXCLUDE REGEX "_test_app\\.cpp$")

add_library(features STATIC
    ${FEATURES_HEADERS} ${FEATURES_SOURCES})
target_include_directories(features PUBLIC generated)
target_link_libraries(features PUBLIC viper)

add_executable(features_test generated/features_test_app.cpp)
target_link_libraries(features_test features cli11)

# src/ is hand-written: the bridge contract, as seen by a developer.
add_executable(features_contract src/contract.cpp)
target_link_libraries(features_contract features)
