# libtiled

A C library for loading Tiled tilemaps in embedded systems and game engines.

## Overview

libtiled provides a lightweight API for loading tilemap data exported from the Tiled map editor. The library consists of two main components:

- **libtiled**: A static library for loading binary tilemap files
- **libtiled-exporter**: A command-line tool for converting Tiled JSON files to an optimized binary format

## Features

- Efficient binary format for tilemap storage
- Support for multiple tile layers
- Support for multiple tilesets
- Minimal memory footprint with packed data structures
- Written in C23 for modern C development

## Building

The project uses CMake for building. Minimum required version is CMake 3.21.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

This will build:
- `lib/libtiled.a` - Static library
- `exporter/libtiled-exporter` - Exporter tool

### CMake Options

- `LIBTILED_BUILD_EXPORTER` (default: ON when building standalone, OFF when included via FetchContent) - Build the exporter tool

### Using with FetchContent

To include libtiled in your project:

```cmake
include(FetchContent)
FetchContent_Declare(
    libtiled
    GIT_REPOSITORY https://github.com/jonkadelic/libtiled.git
    GIT_TAG main
)
FetchContent_MakeAvailable(libtiled)
target_link_libraries(your_target PRIVATE libtiled)
```

By default, the exporter tool will not be built when using FetchContent. To build it anyway, set `LIBTILED_BUILD_EXPORTER` to ON before calling `FetchContent_MakeAvailable`.

## Usage

### Exporting Tilemaps

Convert a Tiled JSON tilemap to binary format:

```bash
./libtiled-exporter path/to/tilemap.json
```

This will generate a `tilemap.json.bin` file in the current directory.

### Loading Tilemaps

Include the library header:

```c
#include <tiled.h>
```

Load a tilemap from a buffer:

```c
tiled_tilemap_t* tilemap = tiled_load_tilemap(buffer_len, buffer);
```

The `tiled_tilemap_t` structure provides access to:
- Tilemap dimensions (`tiles_x`, `tiles_y`)
- Tile size (`tile_size`)
- Layers and their tile data
- Tilesets with their first GID mappings

## Data Structures

### tiled_tilemap_t

```c
typedef struct tiled_tilemap {
    uint8_t tiles_x, tiles_y;
    uint8_t tile_size;
    uint8_t num_layers;
    tiled_tilemap_layer_t* layers;
    uint8_t num_tilesets;
    tiled_tileset_t* tilesets;
} tiled_tilemap_t;
```

### tiled_tilemap_layer_t

```c
typedef struct tiled_tilemap_layer {
    uint16_t* tiles;
} tiled_tilemap_layer_t;
```

### tiled_tileset_t

```c
typedef struct tiled_tileset {
    char name[16];
    uint16_t first_gid;
} tiled_tileset_t;
```

## Dependencies

- [json-c](https://github.com/json-c/json-c) - Automatically fetched by CMake during build

## Requirements

- CMake 3.21 or higher
- C23-compatible compiler
- json-c library (automatically downloaded)

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Example

An example tilemap and tilesets are provided in the `example/` directory demonstrating the expected Tiled JSON format.
