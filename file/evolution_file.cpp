#include "../evolution_core.h"
#include "evolution_file.h"
#include "evolution-core/function/evolution_function.h"


#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h> 
#include <limits.h>
#include <stdlib.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

const s32 MAX_STR = 1024;

std::string File::GetExtension(const c8* file_name) {
    for (u32 i = strlen(file_name); i != 0; i--) {
        if (file_name[i] == '.') {
            return &file_name[i];
        }
    }
    return file_name;
}

std::string File::GetFilePath(const c8* file_name) {
    c8 c8_filename[MAX_STR];
    realpath(file_name , c8_filename);
    return c8_filename;
}

bool File::Delete(const c8* file_name) {
    return remove(file_name) == 0;
}

bool File::Delete(const c8* directory_name, const c8* file_name) {
    c8 c8_filename[MAX_STR];
    s32 len = EVOLUTION::FUNCTION::Strlen(directory_name);
    s32 index = 0;
    for (s32 i; i < len; i++) {
        c8_filename[index++] = directory_name[i];
    }
    len = EVOLUTION::FUNCTION::Strlen(file_name);
    for (s32 i; i < len; i++) {
        c8_filename[index++] = file_name[i];
    }
    c8_filename[index] = '\0';
    return remove(c8_filename) == 0;
}

bool File::IsCheck(const c8* file_name) {
    struct stat st;
    s32 ret;
    ret = stat(file_name, &st);
    return ret == 0;
}

bool File::IsCheck(const c8* directory_name, const c8* file_name) {
    c8 c8_filename[MAX_STR];
    s32 len = EVOLUTION::FUNCTION::Strlen(directory_name);
    s32 index = 0;
    for (s32 i; i < len; i++) {
        c8_filename[index++] = directory_name[i];
    }
    len = EVOLUTION::FUNCTION::Strlen(file_name);
    for (s32 i; i < len; i++) {
        c8_filename[index++] = file_name[i];
    }
    c8_filename[index] = '\0';
    struct stat st;
    return stat(c8_filename, &st) == 0;
}

