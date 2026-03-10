#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct [[gnu::aligned(4)]] tiled_tileset {
    char name[16];
    uint16_t first_gid;
} tiled_tileset_t;

typedef struct [[gnu::aligned(4)]] tiled_tilemap_layer {
    uint16_t* tiles;
} tiled_tilemap_layer_t;

typedef struct [[gnu::aligned(4)]] tiled_tilemap {
    uint8_t tiles_x, tiles_y;
    uint8_t tile_size;
    uint8_t num_layers;
    tiled_tilemap_layer_t* layers;
    uint8_t num_tilesets;
    tiled_tileset_t* tilesets;
} tiled_tilemap_t;

tiled_tilemap_t* tiled_load_tilemap(size_t buffer_len, uint8_t const* buffer);

void tiled_free_tilemap(tiled_tilemap_t* tilemap);
