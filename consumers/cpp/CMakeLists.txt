# The two applications, each compiling the library as applications compile a shared engine, against
# the application's own `shop` and its reads. generated/ belongs to kibo; src/ and common/ are
# written by hand.
file(GLOB LIBRARY_SOURCES library/src/*.cpp)

file(GLOB DATABASE_APP_SOURCES database-app/generated/*.cpp database-app/src/*.cpp)
add_executable(consumers_database_app ${DATABASE_APP_SOURCES} ${LIBRARY_SOURCES})
target_include_directories(consumers_database_app PRIVATE
    database-app/generated library/src common)
target_link_libraries(consumers_database_app viper)

file(GLOB COMMIT_APP_SOURCES commit-app/generated/*.cpp commit-app/src/*.cpp)
add_executable(consumers_commit_app ${COMMIT_APP_SOURCES} ${LIBRARY_SOURCES})
target_include_directories(consumers_commit_app PRIVATE
    commit-app/generated library/src common)
target_link_libraries(consumers_commit_app viper)
