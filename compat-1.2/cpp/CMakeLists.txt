# generated/ belongs to kibo; src/read.cpp is hand-written and is the test.
file(GLOB COMPAT_SOURCES generated/*.cpp)

add_executable(compat_read ${COMPAT_SOURCES} src/read.cpp)
target_include_directories(compat_read PRIVATE generated)
target_link_libraries(compat_read viper)
