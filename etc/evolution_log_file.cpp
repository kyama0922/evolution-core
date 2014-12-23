#include "evolution_log_file.h"
#include <stdio.h>
#include <stdarg.h>

#include <time.h>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;

LogFile::LogFile(const char* file_path){
    this->file_path = NEW char[strlen(file_path) + 1];

    //ファイルパスコピー
    const char* s = file_path;
    char* d = this->file_path;
    while (*d++ = *s++){}

    time_t timer;
    fopen_s(&this->fp, this->file_path, "a");

    time(&timer);
    char time_str[64];
    ctime_s(time_str, 64, &timer);
    fprintf_s(this->fp, "%s : LogStart\n", time_str);
}

LogFile::~LogFile(){
    if (this->fp){
        fclose(this->fp);
    }
    EVOLUTION_DELETE_ARRAY(this->file_path);
}

void LogFile::Write(const char* message){
    fprintf_s(this->fp, "%s\n", message);
}

void LogFile::WriteAndSave(const char* message){
    fprintf_s(this->fp, "%s\n", message);
    fflush(this->fp);
}

void LogFile::Close(){
    if (this->fp){
        fclose(this->fp);
    }
}