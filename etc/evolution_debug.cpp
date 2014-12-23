#include "evolution_debug.h"
#include "evolution_log_file.h"
#include <stdio.h>
#include <stdarg.h>

#include <time.h>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

using namespace EVOLUTION;

const int MAX_STR = 1024;


static EVOLUTION::CORE::LogFile logfile("debug.log");

void Debug::DebugPrint(const char* format, ...){
    va_list args;
    va_start(args, format);

	time_t timer;
	time(&timer);
	char time_str[64];
	ctime_s(time_str, 64, &timer);

    char str[MAX_STR];
    char format_str[MAX_STR];
    
    vsprintf_s(format_str, format, args);
    sprintf_s(str, "%s\n%s\n", time_str, format_str);
    va_end(args);
    printf(str);
#if defined(WIN32) || defined(WIN64)
#if _UNICODE
    wchar_t wout[MAX_STR];
	::size_t size;
    mbstowcs_s(&size, wout, MAX_STR, str, strlen(str));
	OutputDebugString(wout);
#else
	OutputDebugString(str);
#endif //defined(_UNICODE)
#endif //!defined(WIN32) || defined(WIN64)
}

void Debug::DebugLogPrint(const char* format, ...){
    va_list args;
    va_start(args, format);
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_s(time_str, 64, &timer);

    char str[MAX_STR];
    char format_str[MAX_STR];

    vsprintf_s(format_str, format, args);
    sprintf_s(str, "%s\n%s\n", time_str, format_str);
    va_end(args);
    logfile.WriteAndSave(str);

#if defined(WIN32) || defined(WIN64)
#if defined(_UNICODE)
    wchar_t wout[MAX_STR];
    ::size_t size;
    mbstowcs_s(&size, wout, MAX_STR, str, strlen(str));
    OutputDebugString(wout);
#else
    OutputDebugString(str);
#endif //defined(_UNICODE)
#endif //!defined(WIN32) || defined(WIN64)
}

