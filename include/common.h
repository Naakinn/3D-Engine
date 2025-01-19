#ifndef __common_h_
#define __common_h_

#define return_defer(res) \
    do {                  \
        result = res;     \
        goto defer;       \
    } while (0)

#ifndef _STDINT_H
#include <stdint.h>
#endif

/*
 * Reads file contents and stores it in `dst` treated like `char` array.
 * Allocates memory for file named `filepath` contents, caller must free that
 * memory. Returns NULL on error.
 */
char* readFile(const char* filepath);

#endif
