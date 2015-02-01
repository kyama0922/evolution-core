#ifndef __EVOLUTION_DIRECTORY_H_
#define __EVOLUTION_DIRECTORY_H_

#include <evolution_type.h>
#include <vector>
#include <string>

namespace EVOLUTION {
    namespace CORE {
        namespace FILE {

            class Directory {
            public:
                static bool Delete(const c8* directory_name);

                static bool Create(const c8* directory_name);

                static bool IsCheck(const c8* directory_name);

                static bool SetDirectory(const c8* directory_name);

                static std::string GetDirectory();

                static std::vector<std::string> GetFileList(const c8* directory_name);

#if defined(WIN32) || defined(WIN64)
                static bool Delete(const c16* directory_name);
                static bool Create(const c16* directory_name);
                static bool IsCheck(const c16* directory_name);
                static bool SetDirectory(const c16* directory_name);
                static std::vector<std::wstring> GetFileList(const c16* directory_name);
#endif
            };
        }
    }
}
#endif