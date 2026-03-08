# ============================================================================
# libtiled-exporter - Application
# ============================================================================

# Recursively glob all .c files in src/ directory
file(GLOB_RECURSE EXPORTER_SOURCES "src/*.c")

# Create executable
add_executable(libtiled-exporter ${EXPORTER_SOURCES})

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
