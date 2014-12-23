#include "evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;


//16bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
u16 EVOLUTION::FUNCTION::BitSwap(u16 val){
    return ((val >> 8) & 0x00ff) | ((val << 8) & 0xff00);
}
//32bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
u32 EVOLUTION::FUNCTION::BitSwap(u32 val){
    return ((val << 24) & 0xff000000) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00) | ((val >> 24) & 0x000000ff);
}
//64bit�̃r�b�g����ւ��郊�g���G�f�B�A��<==>�r�b�O�G���f�B�A��
u64 EVOLUTION::FUNCTION::BitSwap(u64 val){
    return ((val << 56) & 0xFF00000000000000) | ((val << 40) & 0x00FF000000000000) | ((val << 24) & 0x0000FF0000000000) | ((val << 8) & 0x000000FF00000000) | ((val >> 8) & 0x00000000FF000000) | ((val >> 24) & 0x0000000000FF0000) | ((val >> 40) & 0x000000000000FF00) | ((val >> 56) & 0x00000000000000FF);
}