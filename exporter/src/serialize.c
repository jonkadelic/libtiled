#include "./serialize.h"

#include <stdlib.h>
#include <string.h>

#define TEST 0
#if TEST
#include <tiled.h>
#endif

#include "../../lib/src/internal.h"

bool serialize(json_tilemap_t const* tilemap, size_t num_tilesets, json_tileset_t const tilesets[static num_tilesets], FILE* out) {
    size_t const packet_offset_header = 0;
    size_t const packet_offset_tilemap = packet_offset_header + sizeof(packet_header_t);
    size_t const packet_offset_tiles = packet_offset_tilemap + sizeof(packet_tilemap_t);
    size_t const packet_offset_tilesets = packet_offset_tiles + (sizeof(uint16_t) * tilemap->width * tilemap->height * tilemap->num_layers);
    size_t const packet_offset_end = packet_offset_tilesets + sizeof(packet_tilesets_t) + (sizeof(packet_tileset_t) * num_tilesets);

    uint8_t* const buffer = calloc(1, packet_offset_end);
    if (buffer == nullptr) {
        return false;
    }

    packet_header_t* const packet_header = (packet_header_t*) (buffer + packet_offset_header);
    packet_tilemap_t* const packet_tilemap = (packet_tilemap_t*) (buffer + packet_offset_tilemap);
    uint16_t* const packet_tiles = (uint16_t*) (buffer + packet_offset_tiles);
    packet_tilesets_t* const packet_tilesets = (packet_tilesets_t*) (buffer + packet_offset_tilesets);

    // Init header
    packet_header->magic = MAGIC_WORD;
    packet_header->version = VERSION;
    packet_header->length = packet_offset_end;
    packet_header->offsets.tilemap = packet_offset_tilemap;
    packet_header->offsets.tiles = packet_offset_tiles;
    packet_header->offsets.tilesets = packet_offset_tilesets;

    // Init tilemap
    packet_tilemap->tiles_x = tilemap->width;
    packet_tilemap->tiles_y = tilemap->height;
    packet_tilemap->tile_size = tilemap->tilewidth;
    packet_tilemap->num_layers = tilemap->num_layers;

    // Init tiles
    for (size_t i = 0; i < tilemap->num_layers; i++) {
        json_tilemap_layer_t const* const json_layer = &tilemap->layers[i];
        uint16_t* const packet_layer_tiles = packet_tiles + (tilemap->width * tilemap->height * i);

        for (size_t j = 0; j < tilemap->width * tilemap->height; j++) {
            packet_layer_tiles[j] = (uint16_t) json_layer->data[j];
        }
    }

    // Init tilesets
    packet_tilesets->num_tilesets = num_tilesets;

    for (size_t i = 0; i < num_tilesets; i++) {
        strncpy(packet_tilesets->tilesets[i].name, tilesets[i].name, sizeof(packet_tilesets->tilesets[i].name) - 1);
        packet_tilesets->tilesets[i].first_gid = (uint16_t) tilemap->tilesets[i].firstgid;
    }

#if TEST
    tiled_tilemap_t* tt = tiled_load_tilemap(packet_offset_end, buffer);
    free(tt);
#endif

    if (fwrite(buffer, 1, packet_offset_end, out) != packet_offset_end) {
        free(buffer);
        return false;
    }

    free(buffer);
    return true;
}