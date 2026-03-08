# ============================================================================
# libtiled - Static Library
# ============================================================================

# Recursively glob all .c files in src/ directory
file(GLOB_RECURSE LIBTILED_SOURCES "src/*.c")

# Create static library
add_library(libtiled STATIC ${LIBTILED_SOURCES})

# Add include directory
target_include_directories(libtiled
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Set library properties
set_target_properties(libtiled PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
)
