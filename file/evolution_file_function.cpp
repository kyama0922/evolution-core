#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c8* file_name){
    try{
        FileRead* file_read = NEW FileRead(file_name);
        *pp_file_read = file_read;
    }
    catch (/*FIleException::_EXCEPTION exception*/ ...)
    {
        return EVOLUTION::_RESULT::E_unknown;
    }
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c16* file_name){
    try{
        FileRead* file_read = NEW FileRead(file_name);
        *pp_file_read = file_read;
    }
    catch (/*FIleException::_EXCEPTION exception*/ ...)
    {
        return EVOLUTION::_RESULT::E_unknown;
    }
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode){
    try{
        FileWrite* file_write = NEW FileWrite(file_name, mode);
        *pp_file_write = file_write;
    }
    catch (/*FIleException::_EXCEPTION exception*/ ...)
    {

        return EVOLUTION::_RESULT::E_unknown;
    }
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode){
    try{
        FileWrite* file_write = NEW FileWrite(file_name, mode);
        *pp_file_write = file_write;
    }
    catch (/*FIleException::_EXCEPTION exception*/ ...)
    {

        return EVOLUTION::_RESULT::E_unknown;
    }
    return EVOLUTION::_RESULT::S_ok;
}
