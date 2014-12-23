#ifndef __EVOLUTION_ASSERT_H__
#define __EVOLUTION_ASSERT_H__

namespace EVOLUTION{

    class Assert{
    public:
        static bool DebugAssert(const char* expression, const char* filename, int line);
        static bool DebugAssert(const char* expression, const char* message, const char* filename, int line);
        static bool LogAssert(const char* expression, const char* filename, int line);
    };
}

#define EVOLUTION_ASSERT_LOG(Expression) (void)( (!!(Expression)) || (EVOLUTION::Assert::LogAssert(#Expression , __FILE__ , __LINE__ ) ))

#undef EVOLUTION_ASSERT
#ifdef _DEBUG
#define EVOLUTION_ASSERT(Expression)     (void)( (!!(Expression)) || (EVOLUTION::Assert::DebugAssert(#Expression , __FILE__ , __LINE__ ) ))
#else
#define EVOLUTION_ASSERT(...)     ((void)0)
#endif

#undef EVOLUTION_ASSERT_MESSAGE
#ifdef _DEBUG
#define EVOLUTION_ASSERT_MESSAGE(Expression ,Message)     (void)( (!!(Expression)) || (EVOLUTION::Assert::DebugAssert(#Expression , Message, __FILE__ , __LINE__ ) ))
#else
#define EVOLUTION_ASSERT_MESSAGE(...)      ((void)0)
#endif
#endif //!__EVOLUTION_ASSERT_H__