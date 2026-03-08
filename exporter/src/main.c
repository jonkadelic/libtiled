#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <path_utils.h>
#include <json-c/json.h>

#include "json_objects.h"
#include "serialize.h"
#include "util.h"
#include "verify.h"

int main(int argc, char const* argv[argc]) {
    if (argc != 2) {
        printf("Please specify a tilemap to process.\n");
        return 1;
    }
    char const* const tilemap_path = argv[1];

    char tilemap_abs_path[256];
    char tilemap_dir_path[256];
    char tilemap_basename[256];

    if (make_path_absolute(tilemap_abs_path, sizeof(tilemap_abs_path), tilemap_path) != SUCCESS) {
        printf("Could not get absolute file path!\n");
        return 1;
    }
    if (get_dirname(tilemap_dir_path, sizeof(tilemap_dir_path), tilemap_abs_path) != SUCCESS) {
        printf("Could not get file directory path!\n");
        return 1;
    }
    if (get_basename(tilemap_basename, sizeof(tilemap_basename), tilemap_path) != SUCCESS) {
        printf("Could not get base file name!\n");
        return 1;
    }

    FILE* const tilemap_file = fopen(tilemap_abs_path, "r");
    if (tilemap_file == nullptr) {
        printf("Could not open tilemap file!\n");
        return 1;
    }

    char* const tilemap_text = util__read_file(tilemap_file);
    fclose(tilemap_file);
    if (tilemap_text == nullptr) {
        printf("Could not read tilemap file!\n");
        return 1;
    }

    json_object* const tilemap_object = json_tokener_parse(tilemap_text);
    free(tilemap_text);
    if (tilemap_object == nullptr) {
        printf("Could not tokenize tilemap file!\n");
        return 1;
    }

    json_tilemap_t json_tilemap;
    if (!json_struct__parse(tilemap_object, &JSON_STRUCT_TILEMAP, &json_tilemap)) {
        printf("Could not parse tilemap!\n");
        json_object_put(tilemap_object);
        return 1;
    }
    json_object_put(tilemap_object);

    printf("Successfully parsed tilemap file.\n");

    size_t const num_json_tilesets = json_tilemap.num_tilesets;
    json_tileset_t json_tilesets[num_json_tilesets];
    for (size_t i = 0; i < num_json_tilesets; i++) {
        char tileset_abs_path[256];
        snprintf(tileset_abs_path, sizeof(tileset_abs_path), "%s/%s", tilemap_dir_path, json_tilemap.tilesets[i].source);

        FILE* const tileset_file = fopen(tileset_abs_path, "r");
        if (tileset_file == nullptr) {
            printf("Could not open tileset file \"%s\"!\n", json_tilemap.tilesets[i].source);
            return 1;
        }

        char* const tileset_text = util__read_file(tileset_file);
        fclose(tileset_file);
        if (tileset_text == nullptr) {
            printf("Could not read tileset file \"%s\"!\n", json_tilemap.tilesets[i].source);
            return 1;
        }

        json_object* const tileset_object = json_tokener_parse(tileset_text);
        free(tileset_text);
        if (tileset_object == nullptr) {
            printf("Could not tokenize tileset file \"%s\"!\n", json_tilemap.tilesets[i].source);
            return 1;
        }

        if (!json_struct__parse(tileset_object, &JSON_STRUCT_TILESET, &json_tilesets[i])) {
            printf("Could not parse tileset \"%s\"!\n", json_tilemap.tilesets[i].source);
            json_object_put(tileset_object);
            return 1;
        }
        json_object_put(tileset_object);
    }

    printf("Successfully parsed tilemap tilesets.\n");

    if (!verify(&json_tilemap, num_json_tilesets, json_tilesets)) {
        printf("Failed to validate tilemap.\n");
        return 1;
    }

    printf("Successfully verified tilemap.\n");

    char out_path[256];
    snprintf(out_path, sizeof(out_path), "%s.bin", tilemap_basename);
    FILE* const out_file = fopen(out_path, "w");
    if (out_file == nullptr) {
        printf("Could not open output file!\n");
        return 1;
    }

    if (!serialize(&json_tilemap, num_json_tilesets, json_tilesets, out_file)) {
        printf("Failed to serialize tilemap.\n");
        fclose(out_file);
        return 1;
    }

    printf("Successfully serialized tilemap to \"%s\".\n", out_path);
    fclose(out_file);

    return 0;
}