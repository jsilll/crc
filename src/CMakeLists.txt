file(GLOB SOURCES "*.cpp")

add_executable(kcore ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/include)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(kcore PRIVATE -O3)
endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(kcore PRIVATE -g)
endif()