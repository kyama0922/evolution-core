#ifndef __EVOLUTION_DEBUG_H__
#define __EVOLUTION_DEBUG_H__

namespace EVOLUTION{
    class Debug{
    public:
        static void DebugPrint(const char* format, ...);

        static void DebugLogPrint(const char* format, ...);
    };
}

#undef EVOLUTION_DEBUG_PRINT
#ifdef _DEBUG
#define EVOLUTION_DEBUG_PRINT(fmt, ...)     EVOLUTION::Debug::DebugPrint(fmt , __VA_ARGS__ ,0);
#else
#define EVOLUTION_DEBUG_PRINT(fmt, ...)     ((void)0)
#endif

#undef EVOLUTION_DEBUG_LOG_PRINT
#ifdef _DEBUG
#define EVOLUTION_DEBUG_LOG_PRINT(fmt, ...)   EVOLUTION::Debug::DebugLogPrint(fmt , __VA_ARGS__,0);
#else
#define EVOLUTION_DEBUG_LOG_PRINT(fmt, ...)     ((void)0)
#endif

#endif //!__EVOLUTION_DEBUG_H__