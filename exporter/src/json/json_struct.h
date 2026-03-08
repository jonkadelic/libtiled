#pragma once

#include "./json_field.h"

typedef struct json_struct {
    size_t num_fields;
    json_field_t* fields;
} json_struct_t;

bool json_struct__parse(json_object const* object, json_struct_t const* json_struct, void* out);
