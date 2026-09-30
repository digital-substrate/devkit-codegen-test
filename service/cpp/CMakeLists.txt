# generated/ est le seul endroit où kibo écrit ; src/ est écrit à la main.
#
# C'EST ICI QUE LA DIFFÉRENCE SE VOIT, et c'est la raison d'être de ce site : un pool génère
# une déclaration et laisse l'implémentation au développeur. `ToolsPoolBridges.cpp` et
# `PlayerModelPoolBridges.cpp` sont ce que personne ne peut générer à sa place.
file(GLOB SERVICE_HEADERS generated/*.hpp)
file(GLOB SERVICE_SOURCES generated/*.cpp)

add_library(service STATIC
    ${SERVICE_HEADERS} ${SERVICE_SOURCES})
target_include_directories(service PUBLIC generated)
target_link_libraries(service PUBLIC viper)

add_executable(service_server src/ServiceServer.cpp src/ToolsPoolBridges.cpp src/PlayerModelPoolBridges.cpp)
target_link_libraries(service_server service cli11)

# LE CLIENT NE LIE PAS LES PONTS. `Pool` et `PoolRemote` sont deux features : le côté client
# d'un pool -- `Remote` -- vit dans son propre fichier, et le lieur ne tire de la bibliothèque
# que ce que le client appelle. Quand les deux bords partageaient un `.cpp`, il réclamait
# `tools::add`, une fonction que seul un serveur implémente.
add_executable(service_client src/ServiceClient.cpp)
target_link_libraries(service_client service cli11)
