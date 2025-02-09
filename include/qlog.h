#ifndef __QLOG_H_
#define __QLOG_H_

#include <stdarg.h>

#define qlRED "\033[0;31m"
#define qlGREEN "\033[0;32m"
#define qlYELLOW "\033[0;33m"
#define qlBLUE "\033[0;34m"
#define qlMAGENTA "\033[0;35m"
#define qlCYAN "\033[0;36m"
#define qlWHITE "\033[0;37m"
#define qlRESET "\033[0m"

#define QLOGF(qlLogLevel, format, ...) \
    __qlogf_wrapper(qlLogLevel, __FILE_NAME__, __LINE__, format, ##__VA_ARGS__)

typedef enum { qlINFO, qlDEBUG, qlWARN, qlERROR } qlEnum;

void __qlogf(qlEnum qlLogLevel, const char* filename, unsigned long line,
             const char* format, va_list args);

void __qlogf_wrapper(qlEnum qlLogLevel, const char* filename,
                     unsigned long line, const char* format, ...);

#endif
