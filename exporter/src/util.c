#include "./util.h"

#include <stdlib.h>

char* util__read_file(FILE* file) {
    if (file == nullptr) {
        return nullptr;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        return nullptr;
    }
    long const told = ftell(file);
    if (told < 0) {
        return nullptr;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        return nullptr;
    }

    char* const buffer = calloc(1, told + 1);
    if (buffer == nullptr) {
        return nullptr;
    }

    if (fread(buffer, told, 1, file) != 1) {
        free(buffer);
        return nullptr;
    }

    return buffer;
}