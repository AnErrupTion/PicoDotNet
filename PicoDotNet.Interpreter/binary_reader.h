#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct
{
    uint8_t* data;
    int      sz;
    int      pos;
} BinaryReader;

static inline BinaryReader CreateBinaryReader(const char* fname)
{
    FILE* file = fopen(fname, "r");
    if (file == NULL) { printf("Failed to locate file at '%s'\n", fname); exit(1); }

    fseek(file, 0, SEEK_END);
    size_t sz = ftell(file);
    fseek(file, 0, SEEK_SET);

    uint8_t* buff = (uint8_t*)malloc(sz);
    fread(buff, sz, 1, file);
    fclose(file);

    BinaryReader reader = { buff, (int)sz, 0 };
    return reader;
}

static inline void DisposeBinaryReader(BinaryReader* reader)
{
    if (reader == NULL) { return; }
    if (reader->data != NULL) { free(reader->data); }
}

static inline uint8_t BR_Read8(BinaryReader* reader)
{
    if (reader == NULL) { return 0; }
    uint8_t v = reader->data[reader->pos];
    reader->pos++;
    return v;
}

static inline uint16_t BR_Read16(BinaryReader* reader)
{
    if (reader == NULL) { return 0; }
    uint16_t v = *(uint16_t*)((uintptr_t)reader->data + (uintptr_t)reader->pos);
    reader->pos += 2;
    return v;
}

static inline uint32_t BR_Read32(BinaryReader* reader)
{
    if (reader == NULL) { return 0; }
    uint32_t v = *(uint32_t*)((uintptr_t)reader->data + (uintptr_t)reader->pos);
    reader->pos += 4;
    return v;
}

static inline uint64_t BR_Read64(BinaryReader* reader)
{
    if (reader == NULL) { return 0; }
    uint64_t v = *(uint64_t*)((uintptr_t)reader->data + (uintptr_t)reader->pos);
    reader->pos += 8;
    return v;
}