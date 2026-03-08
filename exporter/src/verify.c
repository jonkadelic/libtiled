#include "./verify.h"

#include <string.h>

bool verify(json_tilemap_t const* tilemap, size_t num_tilesets, json_tileset_t const tilesets[static num_tilesets]) {
    if (tilemap->compressionlevel != -1) {
        return false;
    }

    if (tilemap->height == 0) {
        return false;
    }

    if (tilemap->infinite) {
        return false;
    }

    if (tilemap->num_layers == 0) {
        return false;
    }

    for (size_t i = 0; i < tilemap->num_layers; i++) {
        if (tilemap->layers[i].data_len != tilemap->width * tilemap->height) {
            return false;
        }

        for (size_t j = 0; j < tilemap->width * tilemap->height; j++) {
            if (tilemap->layers[i].data[j] > UINT16_MAX) {
                return false;
            }
        }

        if (tilemap->layers[i].height != tilemap->height) {
            return false;
        }

        if (tilemap->layers[i].opacity != 1.0f) {
            return false;
        }

        if (strcmp(tilemap->layers[i].type, "tilelayer") != 0) {
            return false;
        }

        if (tilemap->layers[i].visible != true) {
            return false;
        }

        if (tilemap->layers[i].width != tilemap->width) {
            return false;
        }

        if (tilemap->layers[i].x != 0) {
            return false;
        }

        if (tilemap->layers[i].y != 0) {
            return false;
        }
    }

    if (strcmp(tilemap->orientation, "orthogonal") != 0) {
        return false;
    }

    if (strcmp(tilemap->renderorder, "right-down") != 0) {
        return false;
    }

    if (tilemap->tileheight == 0) {
        return false;
    }

    if (tilemap->num_tilesets != num_tilesets) {
        return false;
    }

    if (tilemap->tilewidth == 0) {
        return false;
    }

    if (tilemap->tileheight != tilemap->tilewidth) {
        return false;
    }

    if (strcmp(tilemap->type, "map") != 0) {
        return false;
    }

    if (tilemap->width == 0) {
        return false;
    }

    for (size_t i = 0; i < num_tilesets; i++) {
        if (tilesets[i].margin != 0) {
            return false;
        }

        if (tilesets[i].spacing != 0) {
            return false;
        }

        if (tilesets[i].tilecount == 0) {
            return false;
        }

        if (tilesets[i].tileheight != tilemap->tileheight) {
            return false;
        }

        if (tilesets[i].tilewidth != tilemap->tilewidth) {
            return false;
        }

        if (strcmp(tilesets[i].type, "tileset") != 0) {
            return false;
        }
    }

    return true;
}