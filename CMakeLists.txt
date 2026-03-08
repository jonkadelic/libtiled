cmake_minimum_required(VERSION 3.21)

project(libtiled VERSION 1.0.0 LANGUAGES C)

# Set C23 standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# FetchContent for json-c dependency
include(FetchContent)
FetchContent_Declare(
    json-c
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG json-c-0.17-20230812
)
FetchContent_MakeAvailable(json-c)

# Add subdirectories
add_subdirectory(lib)
add_subdirectory(exporter)
