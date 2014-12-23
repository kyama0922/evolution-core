#ifndef __EVOLUTION_LOG_FILE_H__
#define __EVOLUTION_LOG_FILE_H__

#include <evolution_type.h>

namespace EVOLUTION{
    namespace CORE{
        class LogFile{
        private:
            char* file_path;
            FILE* fp;
        public:
            LogFile(const char* file_path);
            ~LogFile();

            void Write(const char* message);
            void WriteAndSave(const char* message);
            void Close();
        };
    }
}

#endif //!__EVOLUTION_LOG_FILE_H__