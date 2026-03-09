#pragma once

#include <stddef.h>
#include <stdint.h>

#define MAGIC_WORD  (0xD00F)
#define VERSION     (0x0001)

/* Packet layout:
 * 1. packet_header_t
 * 2. packet_tilemap_t (at header.offsets.tilemap)
 * 3. uint16_t[] (at header.offsets.tiles)
 * 3. packet_tilesets_t (at header.offsets.tilesets)
 */

typedef struct [[gnu::packed]] packet_header {
    uint16_t magic;
    uint16_t version;
    uint32_t length;
    struct {
        uint32_t tilemap;
        uint32_t tiles;
        uint32_t tilesets;
    } offsets;
} packet_header_t;

typedef struct [[gnu::packed]] packet_tilemap {
    uint8_t tiles_x, tiles_y;
    uint8_t tile_size;
    uint8_t num_layers;
} packet_tilemap_t;

typedef struct [[gnu::packed]] packet_tileset {
    char name[16];
    uint16_t first_gid;
} packet_tileset_t;

typedef struct [[gnu::packed]] packet_tilesets {
    uint8_t num_tilesets;
    packet_tileset_t tilesets[];
} packet_tilesets_t;
