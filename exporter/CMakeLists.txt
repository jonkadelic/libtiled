# ============================================================================
# libtiled-exporter - Application
# ============================================================================

# Recursively glob all .c files in src/ directory
file(GLOB_RECURSE EXPORTER_SOURCES "src/*.c")

# Create executable
add_executable(libtiled-exporter ${EXPORTER_SOURCES})

# FetchContent for json-c dependency
include(FetchContent)
FetchContent_Declare(
    json-c
    GIT_REPOSITORY https://github.com/json-c/json-c.git
    GIT_TAG json-c-0.17-20230812
)
FetchContent_MakeAvailable(json-c)

# Link dependencies
target_link_libraries(libtiled-exporter
    PRIVATE
        tiled
        json-c
        path_utils
)

# Set application properties
set_target_properties(libtiled-exporter PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
)

install(TARGETS libtiled-exporter)
