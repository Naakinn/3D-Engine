#include "common.h"

#include <stdio.h>
#include <stdlib.h>

char* readFile(const char* filepath) {
    char* result = NULL;
    char* buf = NULL;
    FILE* fp = fopen(filepath, "rb");

    if (fp == NULL) return_defer(NULL);
    if (fseek(fp, 0, SEEK_END)) return_defer(NULL);
    long count = ftell(fp);
    if (count < 0) return_defer(NULL);
    rewind(fp);

    buf = (char*)malloc(count);
    if (buf == NULL) return_defer(NULL);
    if (fread(buf, sizeof(char), count, fp) != (size_t)count)
        return_defer(NULL);

    result = buf;
    buf = NULL;

defer:
    if (fp) fclose(fp);
    if (buf) free(buf);
    return result;
}
