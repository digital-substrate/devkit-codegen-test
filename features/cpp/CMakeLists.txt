# Tout ce que kibo écrit est dans generated/, y compris le programme d'épreuve -- il sort du
# template TestApp, personne ne l'a écrit à la main. Il porte un main(), donc il ne peut pas
# entrer dans la bibliothèque : c'est le seul prix d'avoir réuni le généré dans un dossier
# unique, et il se paie ici, en une ligne explicite.
file(GLOB FEATURES_HEADERS generated/*.hpp)
file(GLOB FEATURES_SOURCES generated/*.cpp)
list(FILTER FEATURES_SOURCES EXCLUDE REGEX "_TestApp\\.cpp$")

# CE QUE LE RUNTIME DEVRAIT PORTER ET NE PORTE PAS ENCORE. Viper_TypedCodec et
# Viper_HashAccumulator ne nomment aucun type d'un modèle et ne varient pas d'un modèle à
# l'autre : leur place est dans `src/Viper`. En attendant ils sont compilés ici, et c'est une
# dette, pas un choix -- le pendant C++ du `_codegen` embarqué en Python et TypeScript.
set(PROPOSED ${CMAKE_CURRENT_SOURCE_DIR}/../../runtime-proposed/cpp)
file(GLOB PROPOSED_SOURCES ${PROPOSED}/*.cpp)
file(GLOB PROPOSED_HEADERS ${PROPOSED}/*.hpp)

add_library(features STATIC
    ${FEATURES_HEADERS} ${FEATURES_SOURCES}
    ${PROPOSED_HEADERS} ${PROPOSED_SOURCES})
target_include_directories(features PUBLIC generated ${PROPOSED})
target_link_libraries(features PUBLIC viper)

add_executable(features_test generated/Features_TestApp.cpp)
target_link_libraries(features_test features cli11)
