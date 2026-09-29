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

# LE CLIENT NE DEVRAIT PAS AVOIR À LIER LES PONTS, et il y est obligé. C'est la fusion de
# `Pool` et `PoolRemote` qui le veut : les nouveaux templates mettent les deux bords d'un pool
# -- ce qu'on appelle en processus et ce qu'on appelle au bout d'un fil -- dans un seul
# `Tools_Pool.cpp`. Le client ne veut que le bord distant, mais il reçoit l'objet entier, donc
# le lieur réclame `Tools::add`, une fonction que seul un serveur implémente.
#
# Mesuré ici, au lien, et pas déduit : c'est la démonstration que la scission notée dans
# `templates/cpp/README.md` n'est pas une question de rangement.
add_executable(service_client src/ServiceClient.cpp src/ToolsPoolBridges.cpp src/PlayerModelPoolBridges.cpp)
target_link_libraries(service_client service cli11)
