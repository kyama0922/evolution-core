#include "evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::FUNCTION;

void EVOLUTION::FUNCTION::BitToChar(char out_character[2], const u8 input_data){
    u8 work;

    work = ((input_data >> 4) & 0x0F);
    if (work >= 10){
        out_character[0] = 'a' + work - 10;
    }
    else{
        out_character[0] = '0' + work;
    }

    work = (input_data & 0x0F);
    if (work >= 10){
        out_character[1] = 'a' + work - 10;
    }
    else{
        out_character[1] = '0' + work;
    }
}