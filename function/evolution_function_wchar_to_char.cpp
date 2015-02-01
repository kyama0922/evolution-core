#include "evolution_function.h"
#include <string>

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

//Wcharからcharに変換する

u32 EVOLUTION::FUNCTION::WcharToChar(c8* dest, u32 dest_len, const c16* src) {
    size_t dest_size;
    dest_size = wcstombs(dest, src, wcslen(src) + 1);
    return (u32) dest_size;
}

//Wcharからcharに変換する

u32 EVOLUTION::FUNCTION::WcharToChar(c8* dest, u32 dest_len, const c16* src, u32 src_len) {
    size_t dest_size;
    dest_size = wcstombs(dest, src, src_len);
    return (u32) dest_size;
}