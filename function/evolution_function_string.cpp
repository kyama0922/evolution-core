#include "evolution_function.h"
#include <string>

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;


//文字の長さを取得する
u32 EVOLUTION::FUNCTION::Strlen(const c8* src){
    return (u32)strlen(src);
}
//文字の長さを取得する
u32 EVOLUTION::FUNCTION::Strlen(const c16* src){
    return (u32)wcslen(src);
}