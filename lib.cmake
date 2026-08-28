# Locate the sibling com.digitalsubstrate.viper checkout and build the
# third_parties + viper STATIC targets from its sources, so this repo can
# link against viper without depending on an installed wheel.

set(REPO_VIPER_NAME com.digitalsubstrate.viper)

message(CHECK_START "Looking for ${REPO_VIPER_NAME}")

if (NOT REPO_VIPER AND DEFINED ENV{REPO_VIPER})
    file(TO_CMAKE_PATH "$ENV{REPO_VIPER}" REPO_VIPER)
endif()

if (NOT REPO_VIPER)
    get_filename_component(SIBLING_ROOT ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)
    set(REPO_VIPER ${SIBLING_ROOT}/${REPO_VIPER_NAME})
endif()

if (NOT EXISTS ${REPO_VIPER}/src/Viper)
    message(CHECK_FAIL "not found")
    message(FATAL_ERROR
        "${REPO_VIPER_NAME} checkout is required next to this repository. "
        "Set the REPO_VIPER environment variable, or pass -DREPO_VIPER=<path>.")
else()
    message(CHECK_PASS "found at ${REPO_VIPER}")
endif()

set(REPO_VIPER_TPS ${REPO_VIPER}/third_parties)
set(REPO_VIPER_SRC ${REPO_VIPER}/src)

# Compilation environment
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    add_compile_options(/MP)
endif ()

if (MSVC)
    add_compile_options(/W3 /wd4996 /bigobj)
else ()
    add_compile_options(
        -Wno-shorten-64-to-32
        -Wno-c++2b-extensions
        -Wno-deprecated-declarations
        -Wno-unused-parameter
    )
endif ()

# sqlite
add_definitions(-DSQLITE_MAX_LENGTH=2147483645)
set(SQLITE_FOLDER ${REPO_VIPER_TPS}/sqlite)
file(GLOB SQLITE_HEADERS ${SQLITE_FOLDER}/*.h)
file(GLOB SQLITE_SOURCES ${SQLITE_FOLDER}/*.c)
add_library(sqlite STATIC ${SQLITE_HEADERS} ${SQLITE_SOURCES})
target_include_directories(sqlite PUBLIC ${SQLITE_FOLDER})

# json (header-only, nlohmann)
set(JSON_FOLDER ${REPO_VIPER_TPS}/json)
file(GLOB JSON_HEADERS ${JSON_FOLDER}/nlohmann/*.hpp)
add_library(json INTERFACE)
target_include_directories(json INTERFACE ${JSON_FOLDER})
target_sources(json PRIVATE ${JSON_HEADERS})

# hash
set(HASH_FOLDER ${REPO_VIPER_TPS}/hash)
file(GLOB HASH_HEADERS ${HASH_FOLDER}/*.h)
file(GLOB HASH_SOURCES ${HASH_FOLDER}/*.cpp)
add_library(hash STATIC ${HASH_HEADERS} ${HASH_SOURCES})
target_include_directories(hash PUBLIC ${HASH_FOLDER})

# antlr4
set(ANTLR4_FOLDER ${REPO_VIPER_TPS}/antlr4)
file(GLOB ANTLR4_HEADERS
    ${ANTLR4_FOLDER}/*.h
    ${ANTLR4_FOLDER}/atn/*.h
    ${ANTLR4_FOLDER}/dfa/*.h
    ${ANTLR4_FOLDER}/internal/*.h
    ${ANTLR4_FOLDER}/misc/*.h
    ${ANTLR4_FOLDER}/support/*.h
    ${ANTLR4_FOLDER}/tree/*.h
    ${ANTLR4_FOLDER}/tree/pattern/*.h
    ${ANTLR4_FOLDER}/tree/xpath/*.h
)
file(GLOB ANTLR4_SOURCES
    ${ANTLR4_FOLDER}/*.cpp
    ${ANTLR4_FOLDER}/atn/*.cpp
    ${ANTLR4_FOLDER}/dfa/*.cpp
    ${ANTLR4_FOLDER}/internal/*.cpp
    ${ANTLR4_FOLDER}/misc/*.cpp
    ${ANTLR4_FOLDER}/support/*.cpp
    ${ANTLR4_FOLDER}/tree/*.cpp
    ${ANTLR4_FOLDER}/tree/pattern/*.cpp
    ${ANTLR4_FOLDER}/tree/xpath/*.cpp
)
add_library(antlr4 STATIC ${ANTLR4_HEADERS} ${ANTLR4_SOURCES})
target_include_directories(antlr4 PUBLIC ${ANTLR4_FOLDER})
target_compile_definitions(antlr4 PUBLIC ANTLR4CPP_STATIC)
if (UNIX)
    target_compile_options(antlr4 PRIVATE -Wno-dollar-in-identifier-extension -Wno-sign-compare)
endif ()

# cli11 (header-only)
set(CLI11_FOLDER ${REPO_VIPER_TPS}/cli11)
add_library(cli11 INTERFACE)
target_include_directories(cli11 INTERFACE ${CLI11_FOLDER})

# pugixml
set(PUGIXML_FOLDER ${REPO_VIPER_TPS}/xml/pugixml)
file(GLOB PUGIXML_HEADERS ${PUGIXML_FOLDER}/*.hpp)
file(GLOB PUGIXML_SOURCES ${PUGIXML_FOLDER}/*.cpp)
add_library(pugixml STATIC ${PUGIXML_HEADERS} ${PUGIXML_SOURCES})
target_include_directories(pugixml PUBLIC ${PUGIXML_FOLDER})

# viper
set(VIPER_FOLDER ${REPO_VIPER_SRC}/Viper)
file(GLOB VIPER_HEADERS ${VIPER_FOLDER}/*.h ${VIPER_FOLDER}/*.hpp)
file(GLOB VIPER_SOURCES ${VIPER_FOLDER}/*.cpp)
add_library(viper STATIC ${VIPER_HEADERS} ${VIPER_SOURCES})
target_include_directories(viper PUBLIC ${VIPER_FOLDER})
target_link_libraries(viper PUBLIC antlr4 hash json pugixml sqlite)

if (LINUX)
    target_link_libraries(viper PUBLIC stdc++fs uuid pthread dl)
endif ()
