cmake_minimum_required(VERSION 3.31.6)

project(rlas)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    angelscript
    GIT_REPOSITORY https://github.com/anjo76/angelscript.git
    GIT_TAG v2.38.0
    SOURCE_SUBDIR sdk/angelscript/projects/cmake
)

FetchContent_MakeAvailable(angelscript)

set(ANGELSCRIPT_ADDON_DIR "${angelscript_SOURCE_DIR}/sdk/add_on")

target_sources(angelscript PRIVATE
    ${ANGELSCRIPT_ADDON_DIR}/scriptbuilder/scriptbuilder.cpp
    ${ANGELSCRIPT_ADDON_DIR}/scriptarray/scriptarray.cpp
    ${ANGELSCRIPT_ADDON_DIR}/scriptstdstring/scriptstdstring.cpp
    ${ANGELSCRIPT_ADDON_DIR}/scriptstdstring/scriptstdstring_utils.cpp
)

target_include_directories(angelscript PUBLIC
    "$<BUILD_INTERFACE:${ANGELSCRIPT_ADDON_DIR}/scriptbuilder>"
    "$<BUILD_INTERFACE:${ANGELSCRIPT_ADDON_DIR}/scriptarray>"
    "$<BUILD_INTERFACE:${ANGELSCRIPT_ADDON_DIR}/scriptstdstring>"
)

add_executable(rlas
    src/main.cpp
)

target_link_libraries(rlas PRIVATE raylib angelscript)