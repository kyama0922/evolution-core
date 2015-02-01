#include "evolution_assert.h"
#include "evolution_log_file.h"
#include <stdio.h>
#include <time.h>


using namespace EVOLUTION;

static const int MAX_STR = 1024;

static EVOLUTION::CORE::LogFile logfile("error.log");

bool Assert::DebugAssert(const char* expression, const char* filename, int line) {
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_r(&timer, time_str);

    char str[MAX_STR];
    sprintf(str,
            "----------------------------------Assert----------------------------------\n\n"
            "%s\n"
            "abort(%s) has been called\n%s(%d) \n\n"
            "--------------------------------------------------------------------------\n", time_str, expression, filename, line);
    logfile.WriteAndSave(str);
    return true;
}

bool Assert::DebugAssert(const char* expression, const char* message, const char* filename, int line) {
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_r(&timer, time_str);


    char str[MAX_STR];
    sprintf(str,
            "----------------------------------Assert----------------------------------\n\n"
            "%s\n"
            "Message:%s\n\n"
            "abort(%s) has been called\n%s(%d) \n\n"
            "--------------------------------------------------------------------------\n", time_str, message, expression, filename, line);
    logfile.WriteAndSave(str);
    return true;
}

bool Assert::LogAssert(const char* expression, const char* filename, int line) {
    time_t timer;
    time(&timer);
    char time_str[64];
    ctime_r(&timer, time_str);


    char str[MAX_STR];
    sprintf(str, "%s\nabort(%s) has been called\n%s(%d) \n", time_str, expression, filename, line);
    logfile.WriteAndSave(str);
    return true;
}