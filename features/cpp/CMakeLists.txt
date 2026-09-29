# Tout ce que kibo écrit est dans generated/, y compris le programme d'épreuve -- il sort du
# template TestApp, personne ne l'a écrit à la main. Il porte un main(), donc il ne peut pas
# entrer dans la bibliothèque : c'est le seul prix d'avoir réuni le généré dans un dossier
# unique, et il se paie ici, en une ligne explicite.
file(GLOB FEATURES_HEADERS generated/*.hpp)
file(GLOB FEATURES_SOURCES generated/*.cpp)
list(FILTER FEATURES_SOURCES EXCLUDE REGEX "_TestApp\\.cpp$")

add_library(features STATIC
    ${FEATURES_HEADERS} ${FEATURES_SOURCES})
target_include_directories(features PUBLIC generated)
target_link_libraries(features PUBLIC viper)

add_executable(features_test generated/features_TestApp.cpp)
target_link_libraries(features_test features cli11)
