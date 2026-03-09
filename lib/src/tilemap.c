#include "tiled.h"

#include <stdlib.h>
#include <string.h>

#include "./internal.h"

tiled_tilemap_t* tiled_load_tilemap(size_t buffer_len, uint8_t const* buffer) {
    if (buffer_len < sizeof(packet_header_t) || buffer == nullptr) {
        return nullptr;
    }

    // Validate header
    packet_header_t const* const packet_header = (packet_header_t const*) buffer;
    if (packet_header->magic != MAGIC_WORD) {
        return nullptr;
    }
    if (packet_header->version != VERSION) {
        return nullptr;
    }
    if (buffer_len < packet_header->length) {
        return nullptr;
    }
    if (packet_header->length < packet_header->offsets.tilemap + sizeof(packet_tilemap_t)) {
        return nullptr;
    }
    if (packet_header->length < packet_header->offsets.tiles) {
        return nullptr;
    }
    if (packet_header->length < packet_header->offsets.tilesets + sizeof(packet_tilesets_t)) {
        return nullptr;
    }

    // Set up pointers
    packet_tilemap_t const* const packet_tilemap = (packet_tilemap_t const*) (buffer + packet_header->offsets.tilemap);
    uint16_t const* const packet_tiles = (uint16_t const*) (buffer + packet_header->offsets.tiles);
    packet_tilesets_t const* const packet_tilesets = (packet_tilesets_t const*) (buffer + packet_header->offsets.tilesets);

    // Validate tilemap
    if (packet_tilemap->tiles_x == 0 || packet_tilemap->tiles_y == 0 || packet_tilemap->num_layers == 0) {
        return nullptr;
    }
    if (packet_header->length < packet_header->offsets.tilemap + sizeof(packet_tilemap_t)) {
        return nullptr;
    }

    // Validate tilesets
    if (packet_tilesets->num_tilesets == 0) {
        return nullptr;
    }
    if (packet_header->length < packet_header->offsets.tilesets + sizeof(packet_tilesets_t) + (sizeof(packet_tilesets_t) * packet_tilesets->num_tilesets)) {
        return nullptr;
    }

    // Determine area offsets
    size_t const out_offset_main_area = 0;
    size_t const out_offset_layers_area = out_offset_main_area + sizeof(tiled_tilemap_t);
    size_t const out_offset_tile_data_area = out_offset_layers_area + (sizeof(tiled_tilemap_layer_t) * packet_tilemap->num_layers);
    size_t const out_offset_tilesets_area = out_offset_tile_data_area + (sizeof(uint16_t) * packet_tilemap->tiles_x * packet_tilemap->tiles_y * packet_tilemap->num_layers);
    size_t const out_offset_end = out_offset_tilesets_area + (sizeof(tiled_tileset_t) * packet_tilesets->num_tilesets);
    
    // Allocate external tilemap struct
    tiled_tilemap_t* const out_tilemap = malloc(out_offset_end);
    if (out_tilemap == nullptr) {
        return nullptr;
    }

    // Initialize pointers
    out_tilemap->layers = (tiled_tilemap_layer_t*) (((uint8_t*) out_tilemap) + out_offset_layers_area);
    for (size_t i = 0; i < packet_tilemap->num_layers; i++) {
        out_tilemap->layers[i].tiles = (uint16_t*) (((uint8_t*) out_tilemap) + out_offset_tile_data_area + (sizeof(uint16_t) * packet_tilemap->tiles_x * packet_tilemap->tiles_y * i));
    }
    out_tilemap->tilesets = (tiled_tileset_t*) (((uint8_t*) out_tilemap) + out_offset_tilesets_area);

    // Initialize other data
    out_tilemap->tiles_x = packet_tilemap->tiles_x;
    out_tilemap->tiles_y = packet_tilemap->tiles_y;
    out_tilemap->tile_size = packet_tilemap->tile_size;
    out_tilemap->num_layers = packet_tilemap->num_layers;
    out_tilemap->num_tilesets = packet_tilesets->num_tilesets;

    // Initialize layers
    for (size_t i = 0; i < out_tilemap->num_layers; i++) {
        tiled_tilemap_layer_t* const out_layer = &out_tilemap->layers[i];
        uint16_t const* const packet_layer_tiles = packet_tiles + (packet_tilemap->tiles_x * packet_tilemap->tiles_y * i);

        memcpy(out_layer->tiles, packet_layer_tiles, sizeof(uint16_t) * out_tilemap->tiles_x * out_tilemap->tiles_y);
    }

    // Initialize tilesets
    for (size_t i = 0; i < out_tilemap->num_tilesets; i++) {
        packet_tileset_t const* const packet_tileset = &packet_tilesets->tilesets[i];
        tiled_tileset_t* const out_tileset = &out_tilemap->tilesets[i];

        strncpy(out_tileset->name, packet_tileset->name, sizeof(out_tileset->name));
        out_tileset->first_gid = packet_tileset->first_gid;
    }

    return out_tilemap;
}
