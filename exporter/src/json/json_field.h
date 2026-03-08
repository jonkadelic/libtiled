#pragma once

#include <stddef.h>

#include <json-c/json_types.h>

typedef enum json_field_type json_field_type_t;
typedef struct json_field json_field_t;
typedef struct json_field_data json_field_data_t;

typedef enum json_field_type {
    JSON_FIELD_TYPE__BOOLEAN,
    JSON_FIELD_TYPE__U8,
    JSON_FIELD_TYPE__U16,
    JSON_FIELD_TYPE__U32,
    JSON_FIELD_TYPE__U64,
    JSON_FIELD_TYPE__I8,
    JSON_FIELD_TYPE__I16,
    JSON_FIELD_TYPE__I32,
    JSON_FIELD_TYPE__I64,
    JSON_FIELD_TYPE__F32,
    JSON_FIELD_TYPE__F64,
    JSON_FIELD_TYPE__OBJECT,
    JSON_FIELD_TYPE__ARRAY,
    JSON_FIELD_TYPE__STRING
} json_field_type_t;

typedef struct json_field_data {
    json_field_type_t type;
    union {
        struct {
            size_t num_fields;
            json_field_t* fields;
        } object;
        struct {
            json_field_data_t* field;
        } array;
        struct {
            size_t buffer_size;
        } string;
    } type_data;
} json_field_data_t;

typedef struct json_field {
    size_t offset;
    char name[32];
    json_field_data_t data;
} json_field_t;

bool json_field__get_size(json_object const* object, json_field_data_t const* field, size_t* out);
