#include "evolution_debug.h"
#include "evolution_log_file.h"
#include <stdio.h>
#include <stdarg.h>

#include <time.h>

using namespace EVOLUTION;

const int MAX_STR = 1024;


static EVOLUTION::CORE::LogFile logfile("debug.log");

void Debug::DebugPrint(const char* format, ...) {
    va_list args;
    va_start(args, format);

    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_r(&timer, time_str);

    char str[MAX_STR];
    char format_str[MAX_STR];

    vsprintf(format_str, format, args);
    sprintf(str, "%s\n%s\n", time_str, format_str);
    va_end(args);
    printf(str);
}

void Debug::DebugLogPrint(const char* format, ...) {
    va_list args;
    va_start(args, format);
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_r(&timer, time_str);

    char str[MAX_STR];
    char format_str[MAX_STR];

    vsprintf(format_str, format, args);
    sprintf(str, "%s\n%s\n", time_str, format_str);
    va_end(args);
    logfile.WriteAndSave(str);

}

