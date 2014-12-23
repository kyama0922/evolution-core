#include "evolution_assert.h"
#include "evolution_log_file.h"
#include <stdio.h>
#include <time.h>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

using namespace EVOLUTION;

static const int MAX_STR = 1024;

static EVOLUTION::CORE::LogFile logfile("error.log");

bool Assert::DebugAssert(const char* expression, const char* filename, int line){
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_s(time_str, 64, &timer);

    char str[MAX_STR];
    sprintf_s(str,
        "----------------------------------Assert----------------------------------\n\n"
        "%s\n"
        "abort(%s) has been called\n%s(%d) \n\n"
        "--------------------------------------------------------------------------\n", time_str, expression, filename, line);
    logfile.WriteAndSave(str);

#if defined(WIN32) || defined(WIN64)
#if _UNICODE
    wchar_t wout[MAX_STR];
    ::size_t size;
    mbstowcs_s(&size, wout, MAX_STR, str, strlen(str));
    OutputDebugString(wout);

    if (MessageBox(nullptr, wout, L"ERROR", MB_ABORTRETRYIGNORE | MB_ICONERROR) == IDABORT){
        exit(-1);
    }
#else
    OutputDebugString(str);
    if (MessageBox(nullptr, str, "ERROR", MB_ABORTRETRYIGNORE) == IDABORT){
        exit(-1);
    }
#endif //defined(_UNICODE)
#endif //!defined(WIN32) || defined(WIN64)
    return true;
}

bool Assert::DebugAssert(const char* expression, const char* message, const char* filename, int line){
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_s(time_str, 64, &timer);

    char str[MAX_STR];
    sprintf_s(str,
        "----------------------------------Assert----------------------------------\n\n"
        "%s\n"
        "Message:%s\n\n"
        "abort(%s) has been called\n%s(%d) \n\n"
        "--------------------------------------------------------------------------\n", time_str, message, expression, filename, line);
    logfile.WriteAndSave(str);

#if defined(WIN32) || defined(WIN64)
#if _UNICODE
    wchar_t wout[MAX_STR];
    ::size_t size;
    mbstowcs_s(&size, wout, MAX_STR, str, strlen(str));
    OutputDebugString(wout);

    if (MessageBox(nullptr, wout, L"ERROR", MB_ABORTRETRYIGNORE | MB_ICONERROR) == IDABORT){
        exit(-1);
    }
#else
    OutputDebugString(str);
    if (MessageBox(nullptr, str, "ERROR", MB_ABORTRETRYIGNORE) == IDABORT){
        exit(-1);
    }
#endif //defined(_UNICODE)
#endif //!defined(WIN32) || defined(WIN64)
    return true;
}

bool Assert::LogAssert(const char* expression, const char* filename, int line){
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_s(time_str, 64, &timer);

    char str[MAX_STR];
    sprintf_s(str, "%s\nabort(%s) has been called\n%s(%d) \n", time_str, expression, filename, line);
    logfile.WriteAndSave(str);

#if defined(WIN32) || defined(WIN64)
#if defined(_UNICODE)
    wchar_t wout[MAX_STR];
    ::size_t size;
    mbstowcs_s(&size, wout, MAX_STR, str, strlen(str));
    OutputDebugString(wout);

    if (MessageBox(nullptr, wout, L"ERROR", MB_ABORTRETRYIGNORE | MB_ICONERROR) == IDABORT){
        exit(-1);
    }

#else
    OutputDebugString(str);
    if (MessageBox(nullptr, str, "ERROR", MB_ABORTRETRYIGNORE) == IDABORT){
        exit(-1);
    }
#endif //defined(_UNICODE)
#endif //!defined(WIN32) || defined(WIN64)
    return true;
}