#include "evolution_function.h"
#include <locale.h>

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

//charからWcharに変換する
u32 EVOLUTION::FUNCTION::CharToWChar(c16* dest, u32 dest_len, const c8* src){
    size_t dest_size;
    mbstowcs_s(&dest_size, dest, dest_len, src, strlen(src) + 1);
    return (u32)dest_size;
}

//charからWcharに変換する
u32 EVOLUTION::FUNCTION::CharToWChar(c16* dest, u32 dest_len, const c8* src, u32 src_len){
    size_t dest_size;
    mbstowcs_s(&dest_size, dest, dest_len, src, src_len);
    return (u32)dest_size;
}

