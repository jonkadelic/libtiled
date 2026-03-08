#pragma once

#include "json_objects.h"

bool verify(json_tilemap_t const* tilemap, size_t num_tilesets, json_tileset_t const tilesets[static num_tilesets]);
