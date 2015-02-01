#include "../etc/evolution_assert.h"
#include "evolution_directory.h"
#include "evolution_file.h"
#include "evolution-core/function/evolution_function.h"

#include <string>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

const s32 MAX_STR = 1024;


bool Directory::Delete(const c8* directory_name) {
    return rmdir(directory_name) == 0;
}

bool Directory::Create(const c8* directory_name) {
    return mkdir(directory_name, 0755) == 0;
}

bool Directory::IsCheck(const c8 * directory_name) {
    struct stat st;
    s32 ret;
    ret = stat(directory_name, &st);
    return ret == 0;
}

bool Directory::SetDirectory(const c8 * directory_name) {
    return chdir(directory_name) == 0;
}

std::string Directory::GetDirectory() {
    c8 c8_filename[MAX_STR];
    getcwd(c8_filename, MAX_STR);
    return c8_filename;
}

std::vector<std::string> Directory::GetFileList(const c8 * directory_name) {
    std::vector<std::string> out;
    out.reserve(16);
    DIR *dir;
    struct dirent* file;
    dir = opendir(directory_name);

    for (file = readdir(dir); file != NULL; file = readdir(dir)) {
        out.push_back(file->d_name);
    }
    closedir(dir);
    
    out.reserve(out.size());
    return out;
}