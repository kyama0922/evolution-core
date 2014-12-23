#include "evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

#if defined(HAVE_SSE2) || defined(HAVE_SSE4)
#if defined(HAVE_SSE4)
// SSE4
#  include <smmintrin.h>
#include <intrin.h>
//8bitのビット数を数える
u8 EVOLUTION::FUNCTION::BitCount8(u8 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//16bitのビット数を数える
u16 EVOLUTION::FUNCTION::BitCount16(u16 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//32bitのビット数を数える
u32 EVOLUTION::FUNCTION::BitCount32(u32 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//64bitのビット数を数える
u64 EVOLUTION::FUNCTION::BitCount16(u64 val){
    u64 num = 0;
    for (int i = 0; i < 2; i++) {
#if defined(_X32)
        num += _mm_popcnt_u32(((u32*)&val)[i]);
#elif defined(_X64)
        num += _mm_popcnt_u64(val);
#endif
    }
    return num;
}
#else
// SSE4なしでSSE2
#include <emmintrin.h>
#include <intrin.h>
//8bitのビット数を数える
u8 EVOLUTION::FUNCTION::BitCount8(u8 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//16bitのビット数を数える
u16 EVOLUTION::FUNCTION::BitCount16(u16 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//32bitのビット数を数える
u32 EVOLUTION::FUNCTION::BitCount32(u32 val){
#if defined(_X32)
    return  _mm_popcnt_u32(val);
#elif defined(_X64)
    return  _mm_popcnt_u64(val);
#endif
}

//64bitのビット数を数える
u64 EVOLUTION::FUNCTION::BitCount16(u64 val){
    u64 num = 0;
    for (int i = 0; i < 2; i++) {
#if defined(_X32)
        num += _mm_popcnt_u32(((u32*)&val)[i]);
#elif defined(_X64)
        num += _mm_popcnt_u64(val);
#endif
    }
    return num;
}
#endif
#else

const int BITS_COUNT_TABLE[256] = {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
};

//8bitのビット数を数える
u8 EVOLUTION::FUNCTION::BitCount8(u8 val){
    u8 num = 0;
    for (int i = 0; i<sizeof(val); i++) {
        num += BITS_COUNT_TABLE[((u8*)&val)[i]];
    }
    return num;
}

//16bitのビット数を数える
u16 EVOLUTION::FUNCTION::BitCount16(u16 val){
    u16 num = 0;
    for (int i = 0; i<sizeof(val); i++) {
        num += BITS_COUNT_TABLE[((u8*)&val)[i]];
    }
    return num;
}

//32bitのビット数を数える
u32 EVOLUTION::FUNCTION::BitCount32(u32 val){
    u32 num = 0;
    for (int i = 0; i<sizeof(val); i++) {
        num += BITS_COUNT_TABLE[((u8*)&val)[i]];
    }
    return num;
}

//64bitのビット数を数える
u64 EVOLUTION::FUNCTION::BitCount64(u64 val){
    u64 num = 0;
    for (int i = 0; i<sizeof(val); i++) {
        num += BITS_COUNT_TABLE[((u8*)&val)[i]];
    }
    return num;
}

#endif



