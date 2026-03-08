#include "./json_objects.h"

json_struct_t const JSON_STRUCT_TILEMAP_LAYER = (json_struct_t) {
    .num_fields = 10,
    .fields = (json_field_t[]) {
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, data_len),
            .name = "data",
            .data = {
                .type = JSON_FIELD_TYPE__ARRAY,
                .type_data.array = {
                    .field = &(json_field_data_t) {
                        .type = JSON_FIELD_TYPE__U32
                    }
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, height),
            .name = "height",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, id),
            .name = "id",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, name),
            .name = "name",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_layer_t*) nullptr)->name)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, opacity),
            .name = "opacity",
            .data.type = JSON_FIELD_TYPE__F32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, type),
            .name = "type",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_layer_t*) nullptr)->type)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, visible),
            .name = "visible",
            .data.type = JSON_FIELD_TYPE__BOOLEAN
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, width),
            .name = "width",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, x),
            .name = "x",
            .data.type = JSON_FIELD_TYPE__I32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_layer_t, y),
            .name = "y",
            .data.type = JSON_FIELD_TYPE__I32
        }
    }
};

json_struct_t const JSON_STRUCT_TILEMAP_TILESET = {
    .num_fields = 2,
    .fields = (json_field_t[]) {
        (json_field_t) {
            .offset = offsetof(json_tilemap_tileset_t, firstgid),
            .name = "firstgid",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_tileset_t, source),
            .name = "source",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_tileset_t*) nullptr)->source)
                }
            }
        }
    }
};

json_struct_t const JSON_STRUCT_TILEMAP = (json_struct_t) {
    .num_fields = 15,
    .fields = (json_field_t[]) {
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, compressionlevel),
            .name = "compressionlevel",
            .data.type = JSON_FIELD_TYPE__I32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, height),
            .name = "height",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, infinite),
            .name = "infinite",
            .data.type = JSON_FIELD_TYPE__BOOLEAN
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, num_layers),
            .name = "layers",
            .data = {
                .type = JSON_FIELD_TYPE__ARRAY,
                .type_data.array = {
                    .field = &(json_field_data_t) {
                        .type = JSON_FIELD_TYPE__OBJECT,
                        .type_data.object = {
                            .num_fields = JSON_STRUCT_TILEMAP_LAYER.num_fields,
                            .fields = JSON_STRUCT_TILEMAP_LAYER.fields
                        }
                    }
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, nextlayerid),
            .name = "nextlayerid",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, nextobjectid),
            .name = "nextobjectid",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, orientation),
            .name = "orientation",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_t*) nullptr)->orientation)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, renderorder),
            .name = "renderorder",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_t*) nullptr)->renderorder)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, tiledversion),
            .name = "tiledversion",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_t*) nullptr)->tiledversion)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, tileheight),
            .name = "tileheight",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, num_tilesets),
            .name = "tilesets",
            .data = {
                .type = JSON_FIELD_TYPE__ARRAY,
                .type_data.array = {
                    .field = &(json_field_data_t) {
                        .type = JSON_FIELD_TYPE__OBJECT,
                        .type_data.object = {
                            .num_fields = JSON_STRUCT_TILEMAP_TILESET.num_fields,
                            .fields = JSON_STRUCT_TILEMAP_TILESET.fields
                        }
                    }
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, tilewidth),
            .name = "tilewidth",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, type),
            .name = "type",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_t*) nullptr)->type)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, version),
            .name = "version",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tilemap_t*) nullptr)->version)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tilemap_t, width),
            .name = "width",
            .data.type = JSON_FIELD_TYPE__U32
        }
    }
};

json_struct_t const JSON_STRUCT_TILESET = (json_struct_t) {
    .num_fields = 13,
    .fields = (json_field_t[]) {
        (json_field_t) {
            .offset = offsetof(json_tileset_t, columns),
            .name = "columns",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, image),
            .name = "image",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tileset_t*) nullptr)->image)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, imageheight),
            .name = "imageheight",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, imagewidth),
            .name = "imagewidth",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, margin),
            .name = "margin",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, name),
            .name = "name",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tileset_t*) nullptr)->name)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, spacing),
            .name = "spacing",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, tilecount),
            .name = "tilecount",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, tiledversion),
            .name = "tiledversion",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tileset_t*) nullptr)->tiledversion)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, tileheight),
            .name = "tileheight",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, tilewidth),
            .name = "tilewidth",
            .data.type = JSON_FIELD_TYPE__U32
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, type),
            .name = "type",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tileset_t*) nullptr)->type)
                }
            }
        },
        (json_field_t) {
            .offset = offsetof(json_tileset_t, version),
            .name = "version",
            .data = {
                .type = JSON_FIELD_TYPE__STRING,
                .type_data.string = {
                    .buffer_size = sizeof(((json_tileset_t*) nullptr)->version)
                }
            }
        }
    }
};
