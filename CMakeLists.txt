cmake_minimum_required(VERSION 3.21)

project(libtiled VERSION 1.0.0 LANGUAGES C)

# Set C23 standard
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Option to build exporter (disabled by default when used via FetchContent)
option(LIBTILED_BUILD_EXPORTER "Build the libtiled exporter tool" ${PROJECT_IS_TOP_LEVEL})

# Add subdirectories
add_subdirectory(lib)
if(LIBTILED_BUILD_EXPORTER)
    add_subdirectory(exporter)
endif()
