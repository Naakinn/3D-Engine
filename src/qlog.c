#include "qlog.h"

#include <stdio.h>

void __qlogf(qlEnum qlLogLevel, const char* filename, unsigned long line,
             const char* format, va_list args) {
    switch (qlLogLevel) {
        case qlINFO:
            printf("[INFO] (%s:%lu) ", filename, line);
            break;
        case qlDEBUG:
            printf(qlCYAN "[DEBUG] (%s:%lu) ", filename, line);
            break;
        case qlWARN:
            printf(qlYELLOW "[WARN] (%s:%lu) ", filename, line);
            break;
        case qlERROR:
            fprintf(stderr, qlRED "[ERROR] (%s:%lu) ", filename, line);
            break;
    }
    vprintf(format, args);
    printf(qlRESET);
}

void __qlogf_wrapper(qlEnum qlLogLevel, const char* filename,
                     unsigned long line, const char* format, ...) {
#ifndef DEBUG
    if (qlLogLevel == qlDEBUG) return;
#endif
    va_list args;
    va_start(args, format);
    __qlogf(qlLogLevel, filename, line, format, args);
    va_end(args);
}
