cmake_minimum_required(VERSION 3.20)

project(
    Forge
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Forge
    src/main.cpp
)

if (MSVC)
    target_compile_options(
        Forge
        PRIVATE
        /source-charset:utf-8
        /execution-charset:.1251
    )
endif()