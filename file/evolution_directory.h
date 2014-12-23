#ifndef __EVOLUTION_DIRECTORY_H_
#define __EVOLUTION_DIRECTORY_H_

#include <evolution_type.h>
#include <vector>
#include <string>

namespace EVOLUTION{
    namespace CORE{
        namespace FILE{
            class Directory{
            public:
                static bool Delete(const char* directory_name);
                static bool Delete(const wchar_t* directory_name);

                static bool Create(const char* directory_name);
                static bool Create(const wchar_t* directory_name);

                static bool IsCheck(const char* directory_name);
                static bool IsCheck(const wchar_t* directory_name);

                static bool SetDirectory(const char* directory_name);
                static bool SetDirectory(const wchar_t* directory_name);

                static std::string GetDirectory();

                static std::vector<std::string> GetFileList(const char* directory_name);
                static std::vector<std::wstring>  GetFileList(const wchar_t* directory_name);
            };
        }
    }
}
#endif