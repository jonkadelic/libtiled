#include "./json_field.h"

#include <stdint.h>

#include <json-c/json.h>

static bool size_boolean(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_u8(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_u16(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_u32(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_u64(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_i8(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_i16(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_i32(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_i64(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_f32(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_f64(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_object(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_array(json_object const* object, json_field_data_t const* field, size_t* out);
static bool size_string(json_object const* object, json_field_data_t const* field, size_t* out);

typedef bool (*fn_size_t)(json_object const*, json_field_data_t const*, size_t*);

static fn_size_t const SIZES[] = {
    [JSON_FIELD_TYPE__BOOLEAN] = size_boolean,
    [JSON_FIELD_TYPE__U8] = size_u8,
    [JSON_FIELD_TYPE__U16] = size_u16,
    [JSON_FIELD_TYPE__U32] = size_u32,
    [JSON_FIELD_TYPE__U64] = size_u64,
    [JSON_FIELD_TYPE__I8] = size_i8,
    [JSON_FIELD_TYPE__I16] = size_i16,
    [JSON_FIELD_TYPE__I32] = size_i32,
    [JSON_FIELD_TYPE__I64] = size_i64,
    [JSON_FIELD_TYPE__F32] = size_f32,
    [JSON_FIELD_TYPE__F64] = size_f64,
    [JSON_FIELD_TYPE__OBJECT] = size_object,
    [JSON_FIELD_TYPE__ARRAY] = size_array,
    [JSON_FIELD_TYPE__STRING] = size_string,
};

bool json_field__get_size(json_object const* object, json_field_data_t const* field, size_t* out) {
    fn_size_t const size_fn = SIZES[field->type];

    return size_fn(object, field, out);
}

static bool size_boolean(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(bool);
    return true;
}

static bool size_u8(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(uint8_t);
    return true;
}

static bool size_u16(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(uint16_t);
    return true;
}

static bool size_u32(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(uint32_t);
    return true;
}

static bool size_u64(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(uint64_t);
    return true;
}

static bool size_i8(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(int8_t);
    return true;
}

static bool size_i16(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(int16_t);
    return true;
}

static bool size_i32(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(int32_t);
    return true;
}

static bool size_i64(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(int64_t);
    return true;
}

static bool size_f32(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(float);
    return true;
}

static bool size_f64(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(double);
    return true;
}

static bool size_object(json_object const* object, json_field_data_t const* field, size_t* out) {
    size_t acc = 0;

    if (json_object_get_type(object) != json_type_object) {
        return false;
    }

    for (size_t i = 0; i < field->type_data.object.num_fields; i++) {
        json_field_t const* const child_field = &field->type_data.object.fields[i];
        fn_size_t const size_fn = SIZES[child_field->data.type];

        json_object* child_object = nullptr;
        if (json_object_object_get_ex(object, child_field->name, &child_object)) {
            size_t size = 0;

            if (!size_fn(child_object, &child_field->data, &size)) {
                return false;
            }

            acc += size;
        } else {
            return false;
        }
    }

    *out = acc;
    return true;
}

static bool size_array(json_object const* object, json_field_data_t const* field, size_t* out) {
    size_t acc = 0;

    if (json_object_get_type(object) != json_type_array) {
        return false;
    }

    size_t const array_len = json_object_array_length(object);

    fn_size_t const size_fn = SIZES[field->type_data.array.field->type];

    for (size_t i = 0; i < array_len; i++) {
        size_t size = 0;

        if (!size_fn(json_object_array_get_idx(object, i), field->type_data.array.field, &size)) {
            return false;
        }

        acc += size;
    }

    *out = acc;
    return true;
}

static bool size_string(json_object const* object, json_field_data_t const* field, size_t* out) {
    *out = sizeof(char) * field->type_data.string.buffer_size;
    return true;
}
