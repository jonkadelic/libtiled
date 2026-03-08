#pragma once

#include <stddef.h>
#include <stdint.h>

#include "json/json_struct.h"

typedef struct [[gnu::packed]] json_tilemap_layer {
    size_t data_len;
    uint32_t* data;
    uint32_t height;
    uint32_t id;
    char name[32];
    float opacity;
    char type[16];
    bool visible;
    uint32_t width;
    int32_t x;
    int32_t y;
} json_tilemap_layer_t;

typedef struct [[gnu::packed]] json_tilemap_tileset {
    uint32_t firstgid;
    char source[256];
} json_tilemap_tileset_t;

typedef struct [[gnu::packed]] json_tilemap {
    int32_t compressionlevel;
    uint32_t height;
    bool infinite;
    size_t num_layers;
    json_tilemap_layer_t* layers;
    uint32_t nextlayerid;
    uint32_t nextobjectid;
    char orientation[32];
    char renderorder[32];
    char tiledversion[16];
    uint32_t tileheight;
    size_t num_tilesets;
    json_tilemap_tileset_t* tilesets;
    uint32_t tilewidth;
    char type[16];
    char version[16];
    uint32_t width;
} json_tilemap_t;

typedef struct [[gnu::packed]] json_tileset {
    uint32_t columns;
    char image[64];
    uint32_t imageheight;
    uint32_t imagewidth;
    uint32_t margin;
    char name[64];
    uint32_t spacing;
    uint32_t tilecount;
    char tiledversion[16];
    uint32_t tileheight;
    uint32_t tilewidth;
    char type[16];
    char version[16];
} json_tileset_t;

extern json_struct_t const JSON_STRUCT_TILEMAP_LAYER;
extern json_struct_t const JSON_STRUCT_TILEMAP_TILESET;
extern json_struct_t const JSON_STRUCT_TILEMAP;

extern json_struct_t const JSON_STRUCT_TILESET;
