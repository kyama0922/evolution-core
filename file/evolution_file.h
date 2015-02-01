#ifndef __EVOLUTION_FILE_H_
#define __EVOLUTION_FILE_H_

#include <evolution_type.h>
#include <vector>
#include <string>

namespace EVOLUTION {
    namespace CORE {
        namespace FILE {

            class File {
            public:

                static std::string GetExtension(const c8* file_name);

                static std::string GetFilePath(const c8* file_name);

                static bool Delete(const c8* file_name);

                static bool Delete(const c8* directory_name, const c8* file_name);

                static bool IsCheck(const c8* file_name);

                static bool IsCheck(const c8* directory_name, const c8* file_name);

#if defined(WIN32) || defined(WIN64)
                static std::wstring GetExtension(const c16* file_name);
                static std::wstring GetFilePath(const c16* file_name);
                static bool Delete(const c16* file_name);
                static bool Delete(const c16* directory_name, const c16* file_name);
                static bool IsCheck(const c16* file_name);
                static bool IsCheck(const c16* directory_name, const c16* file_name);
#endif
            };
        }
    }
}

#endif