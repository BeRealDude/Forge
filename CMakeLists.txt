cmake_minimum_required(VERSION 3.20)

project(
    Forge
    VERSION 0.1.0
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Forge
    src/main.cpp
    src/Note.cpp
    src/Note.h
    src/NoteRepository.cpp
    src/NoteRepository.h
     src/InputHandle.cpp
     src/InputHandle.h
     src/TextUI.cpp
     src/TextUI.h
     src/CommandsHandle.cpp
     src/CommandsHandle.h
     src/NoteFileStorage.h
     src/NoteFileStorage.cpp
)

target_link_libraries(
    Forge
    PRIVATE nlohmann_json::nlohmann_json
)

if (MSVC)
    target_compile_options(
        Forge
        PRIVATE
        /utf-8
    )
endif()