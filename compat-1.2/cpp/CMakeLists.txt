# generated/ est à kibo ; src/read.cpp est écrit à la main, et c'est l'épreuve.
file(GLOB COMPAT_SOURCES generated/*.cpp)

# Ce que le runtime devrait porter et ne porte pas encore -- dette, comme sur les autres sites.
set(PROPOSED ${CMAKE_CURRENT_SOURCE_DIR}/../../runtime-proposed/cpp)
file(GLOB PROPOSED_SOURCES ${PROPOSED}/*.cpp)

add_executable(compat_read ${COMPAT_SOURCES} ${PROPOSED_SOURCES} src/read.cpp)
target_include_directories(compat_read PRIVATE generated ${PROPOSED})
target_link_libraries(compat_read viper)
