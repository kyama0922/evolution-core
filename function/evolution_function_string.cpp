#include "evolution_function.h"
#include <string>

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;


//�����̒������擾����
u32 EVOLUTION::FUNCTION::Strlen(const c8* src){
    return (u32)strlen(src);
}
//�����̒������擾����
u32 EVOLUTION::FUNCTION::Strlen(const c16* src){
    return (u32)wcslen(src);
}