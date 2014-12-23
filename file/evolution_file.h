#ifndef __EVOLUTION_FILE_H_
#define __EVOLUTION_FILE_H_

#include <evolution_type.h>
#include <vector>
#include <string>

namespace EVOLUTION{
    namespace CORE{
        namespace FILE{
            class File{
            public:
                static std::string GetExtension(const char* file_name);
                static std::wstring GetExtension(const wchar_t* file_name);

                static std::string GetFilePath(const char* file_name);
                static std::wstring GetFilePath(const wchar_t* file_name);


                static bool Delete(const char* file_name);
                static bool Delete(const wchar_t* file_name);

                static bool Delete(const char* directory_name, const char* file_name);
                static bool Delete(const wchar_t* directory_name, const wchar_t* file_name);

                static bool IsCheck(const char* file_name);
                static bool IsCheck(const wchar_t* file_name);

                static bool IsCheck(const char* directory_name, const char* file_name);
                static bool IsCheck(const wchar_t* directory_name, const wchar_t* file_name);
            };
        }
    }
}

#endif