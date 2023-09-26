cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPT_WARNINGS_AS_ERRORS_DEVELOPER_DEFAULT ON)

project(KCore
        VERSION 0.1.0
        LANGUAGES CXX)

if (MSVC)
    add_compile_options(/W4 /w14640)
else ()
    add_compile_options(
            -Wall -Wextra -Wshadow -Wunused -Wnon-virtual-dtor -pedantic)
endif ()

find_package(Boost REQUIRED)

add_subdirectory(src)