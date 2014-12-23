#include "evolution_function.h"
#include <string>

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

//Wchar‚©‚çchar‚É•ÏŠ·‚·‚é
u32 EVOLUTION::FUNCTION::WcharToChar(c8* dest, u32 dest_len, const c16* src){
    size_t dest_size;
    wcstombs_s(&dest_size, dest, dest_len, src, wcslen(src) + 1);
    return (u32)dest_size;
}

//Wchar‚©‚çchar‚É•ÏŠ·‚·‚é
u32 EVOLUTION::FUNCTION::WcharToChar(c8* dest, u32 dest_len, const c16* src, u32 src_len){
    size_t dest_size;
    wcstombs_s(&dest_size, dest, dest_len, src, src_len);
    return (u32)dest_size;
}