#ifndef __common_h_
#define __common_h_

#define return_defer(res) \
    do {                  \
        result = res;     \
        goto defer;       \
    } while (0)

#include <stdint.h>

/*
 * Reads file contents and stores it in `dst` treated like `char` array.
 * Allocates memory for file named `filepath` contents, caller must free that
 * memory. Returns NULL on error.
 */
char* readFile(const char* filepath);

#endif
