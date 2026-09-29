# generated/ est à kibo ; src/read.cpp est écrit à la main, et c'est l'épreuve.
file(GLOB COMPAT_SOURCES generated/*.cpp)

add_executable(compat_read ${COMPAT_SOURCES} src/read.cpp)
target_include_directories(compat_read PRIVATE generated)
target_link_libraries(compat_read viper)
