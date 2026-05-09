file(GLOB SERVICE_HEADERS Service/*.hpp)
file(GLOB SERVICE_SOURCES Service/*.cpp)

add_library(service STATIC ${SERVICE_HEADERS} ${SERVICE_SOURCES})
target_include_directories(service PUBLIC Service)
target_link_libraries(service PUBLIC viper)

add_executable(service_server ServiceServer.cpp Service_FunctionPoolBridges.cpp Service_AttachmentFunctionPoolBridges.cpp)
target_link_libraries(service_server service cli11)

add_executable(service_client ServiceClient.cpp)
target_link_libraries(service_client service cli11)


