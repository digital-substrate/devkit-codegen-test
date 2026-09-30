# generated/ is the only place kibo writes; src/ is hand-written.
#
# This is the point of this site: a pool generates a declaration and leaves the
# implementation to the developer. `ToolsPoolBridges.cpp` and `PlayerModelPoolBridges.cpp`
# are what cannot be generated.
file(GLOB SERVICE_HEADERS generated/*.hpp)
file(GLOB SERVICE_SOURCES generated/*.cpp)

add_library(service STATIC
    ${SERVICE_HEADERS} ${SERVICE_SOURCES})
target_include_directories(service PUBLIC generated)
target_link_libraries(service PUBLIC viper)

add_executable(service_server src/ServiceServer.cpp src/ToolsPoolBridges.cpp src/PlayerModelPoolBridges.cpp)
target_link_libraries(service_server service cli11)

# The client does not link the bridges. `Pool` and `PoolRemote` are two features: the client
# side of a pool (`Remote`) lives in its own file, so the linker pulls from the library only
# what the client calls. When both sides shared one `.cpp`, the client required `tools::add`,
# a function only a server implements.
add_executable(service_client src/ServiceClient.cpp)
target_link_libraries(service_client service cli11)
