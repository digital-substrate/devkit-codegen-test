file(GLOB FEATURES_HEADERS Features/*.hpp)
file(GLOB FEATURES_SOURCES Features/*.cpp)

add_library(features STATIC ${FEATURES_HEADERS} ${FEATURES_SOURCES})
target_include_directories(features PUBLIC Features)
target_link_libraries(features PUBLIC viper)

add_executable(test_codec Features_Test_Codec.cpp)
target_link_libraries(test_codec features cli11)

add_executable(test_database Features_Test_Database.cpp)
target_link_libraries(test_database features cli11)

add_executable(test_database_fuzz Features_Test_DatabaseFuzz.cpp)
target_link_libraries(test_database_fuzz features cli11)

add_executable(test_database_remote Features_Test_DatabaseRemote.cpp)
target_link_libraries(test_database_remote features cli11)
