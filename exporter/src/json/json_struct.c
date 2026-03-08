#include "./json_struct.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <json-c/json.h>

static bool parse_boolean(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_u8(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_u16(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_u32(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_u64(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_i8(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_i16(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_i32(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_i64(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_f32(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_f64(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_object(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_array(json_object const* object, json_field_data_t const* field, void* out);
static bool parse_string(json_object const* object, json_field_data_t const* field, void* out);

typedef bool (*fn_parser_t)(json_object const*, json_field_data_t const*, void*);

static fn_parser_t const PARSERS[] = {
    [JSON_FIELD_TYPE__BOOLEAN] = parse_boolean,
    [JSON_FIELD_TYPE__U8] = parse_u8,
    [JSON_FIELD_TYPE__U16] = parse_u16,
    [JSON_FIELD_TYPE__U32] = parse_u32,
    [JSON_FIELD_TYPE__U64] = parse_u64,
    [JSON_FIELD_TYPE__I8] = parse_i8,
    [JSON_FIELD_TYPE__I16] = parse_i16,
    [JSON_FIELD_TYPE__I32] = parse_i32,
    [JSON_FIELD_TYPE__I64] = parse_i64,
    [JSON_FIELD_TYPE__F32] = parse_f32,
    [JSON_FIELD_TYPE__F64] = parse_f64,
    [JSON_FIELD_TYPE__OBJECT] = parse_object,
    [JSON_FIELD_TYPE__ARRAY] = parse_array,
    [JSON_FIELD_TYPE__STRING] = parse_string,
};

bool json_struct__parse(json_object const* object, json_struct_t const* json_struct, void* out) {
    if (json_object_get_type(object) != json_type_object) {
        return false;
    }

    for (size_t i = 0; i < json_struct->num_fields; i++) {
        json_field_t const* const child_field = &json_struct->fields[i];
        fn_parser_t const parser_fn = PARSERS[child_field->data.type];
        void* const child_out = ((uint8_t*) out) + child_field->offset;

        json_object* child_object = nullptr;
        if (json_object_object_get_ex(object, child_field->name, &child_object)) {
            if (!parser_fn(child_object, &child_field->data, child_out)) {
                return false;
            }
        } else {
            return false;
        }
    }

    return true;
}

static bool parse_boolean(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_boolean) {
        return false;
    }

    bool* const c_out = (bool*) out;

    *c_out = json_object_get_boolean(object);

    return true;
}

static bool parse_u8(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < 0 || value > UINT8_MAX) {
        return false;
    }

    uint8_t* const c_out = (uint8_t*) out;

    *c_out = (uint8_t) value;

    return true;
}

static bool parse_u16(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < 0 || value > UINT16_MAX) {
        return false;
    }

    uint16_t* const c_out = (uint16_t*) out;

    *c_out = (uint16_t) value;

    return true;
}

static bool parse_u32(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < 0 || value > UINT32_MAX) {
        return false;
    }

    uint32_t* const c_out = (uint32_t*) out;

    *c_out = (uint32_t) value;

    return true;
}

static bool parse_u64(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    uint64_t const uvalue = json_object_get_uint64(object);
    int64_t const ivalue = json_object_get_int64(object);

    uint64_t value;
    if (uvalue == ivalue || (uvalue != ivalue && ivalue == INT64_MAX)) {
        value = uvalue;
    } else {
        return false;
    }

    uint64_t* const c_out = (uint64_t*) out;

    *c_out = (uint64_t) value;

    return true;
}

static bool parse_i8(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < INT8_MIN || value > INT8_MAX) {
        return false;
    }

    int8_t* const c_out = (int8_t*) out;

    *c_out = (int8_t) value;

    return true;
}

static bool parse_i16(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < INT16_MIN || value > INT16_MAX) {
        return false;
    }

    int16_t* const c_out = (int16_t*) out;

    *c_out = (int16_t) value;

    return true;
}

static bool parse_i32(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    int64_t const value = json_object_get_int64(object);
    if (value < INT8_MIN || value > INT8_MAX) {
        return false;
    }

    int32_t* const c_out = (int32_t*) out;

    *c_out = (int32_t) value;

    return true;
}

static bool parse_i64(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_int) {
        return false;
    }

    uint64_t const uvalue = json_object_get_uint64(object);
    int64_t const ivalue = json_object_get_int64(object);

    int64_t value;
    if (uvalue == ivalue || (uvalue != ivalue && uvalue == 0)) {
        value = ivalue;
    } else {
        return false;
    }

    uint64_t* const c_out = (uint64_t*) out;

    *c_out = (uint64_t) value;

    return true;
}

static bool parse_f32(json_object const* object, json_field_data_t const* field, void* out) {
    json_type const type = json_object_get_type(object);
    if (type != json_type_double && type != json_type_int) {
        return false;
    }

    double const value = json_object_get_double(object);

    float* const c_out = (float*) out;

    *c_out = (float) value;

    return true;
}

static bool parse_f64(json_object const* object, json_field_data_t const* field, void* out) {
    json_type const type = json_object_get_type(object);
    if (type != json_type_double && type != json_type_int) {
        return false;
    }

    double const value = json_object_get_double(object);

    double* const c_out = (double*) out;

    *c_out = value;

    return true;
}

static bool parse_object(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_object) {
        return false;
    }

    for (size_t i = 0; i < field->type_data.object.num_fields; i++) {
        json_field_t const* const child_field = &field->type_data.object.fields[i];
        fn_parser_t const parser_fn = PARSERS[child_field->data.type];
        void* const child_out = ((uint8_t*) out) + child_field->offset;

        json_object* child_object = nullptr;
        if (json_object_object_get_ex(object, child_field->name, &child_object)) {
            if (!parser_fn(child_object, &child_field->data, child_out)) {
                return false;
            }
        } else {
            return false;
        }
    }

    return true;
}

static bool parse_array(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_array) {
        return false;
    }

    size_t const array_len = json_object_array_length(object);

    size_t array_size;
    if (!json_field__get_size(object, field, &array_size)) {
        return false;
    }

    size_t* const out_array_len = out;
    *out_array_len = array_len;

    void** const c_out = (void**) (((uint8_t*) out) + sizeof(size_t));

    *c_out = malloc(array_size);
    assert(*c_out != nullptr);

    fn_parser_t const parser_fn = PARSERS[field->type_data.array.field->type];

    void* offset_ptr = *c_out;
    for (size_t i = 0; i < array_len; i++) {
        json_object const* const child_object = json_object_array_get_idx(object, i);
        size_t child_size;
        if (!json_field__get_size(child_object, field->type_data.array.field, &child_size)) {
            free(*c_out);
            return false;
        }

        if (!parser_fn(child_object, field->type_data.array.field, offset_ptr)) {
            free(*c_out);
            return false;
        }

        offset_ptr = ((uint8_t*) offset_ptr) + child_size;
    }

    return true;
}

static bool parse_string(json_object const* object, json_field_data_t const* field, void* out) {
    if (json_object_get_type(object) != json_type_string) {
        return false;
    }

    size_t const string_len = json_object_get_string_len(object);
    if (string_len >= field->type_data.string.buffer_size) {
        return false;
    }

    char const* const string = json_object_get_string((void*) object);

    strncpy(out, string, field->type_data.string.buffer_size);

    return true;
}
