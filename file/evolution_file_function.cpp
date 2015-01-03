#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c8* file_name){
    FileRead* file_read = NEW FileRead();

    if (EVOLUTION_FAILED(file_read->Create(file_name)))
    {
        file_read->Release();
        *pp_file_read = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_file_read = file_read;
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c16* file_name){
    FileRead* file_read = NEW FileRead();

    if (EVOLUTION_FAILED(file_read->Create(file_name)))
    {
        file_read->Release();
        *pp_file_read = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_file_read = file_read;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode){
    FileWrite* file_write = NEW FileWrite();

    if (EVOLUTION_FAILED(file_write->Create(file_name, mode)))
    {
        file_write->Release();
        *pp_file_write = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_file_write = file_write;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode){
    FileWrite* file_write = NEW FileWrite();

    if (EVOLUTION_FAILED(file_write->Create(file_name, mode)))
    {
        file_write->Release();
        *pp_file_write = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_file_write = file_write;
    return EVOLUTION::_RESULT::S_ok;
}


EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateTextFileRead(CORE::FILE::ITextFileRead** pp_text_file_read, const c8* file_name){
    TextFileRead* file_read = NEW TextFileRead();

    if (EVOLUTION_FAILED(file_read->Create(file_name)))
    {
        file_read->Release();
        *pp_text_file_read = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_text_file_read = file_read;
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateTextFileRead(CORE::FILE::ITextFileRead** pp_text_file_read, const c16* file_name){
    TextFileRead* file_read = NEW TextFileRead();

    if (EVOLUTION_FAILED(file_read->Create(file_name)))
    {
        file_read->Release();
        *pp_text_file_read = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_text_file_read = file_read;
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateTextFileWrite(CORE::FILE::ITextFileWrite** pp_text_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode){
    TextFileWrite* file_write = NEW TextFileWrite();

    if (EVOLUTION_FAILED(file_write->Create(file_name, mode)))
    {
        file_write->Release();
        *pp_text_file_write = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_text_file_write = file_write;
    return EVOLUTION::_RESULT::S_ok;
}

EVOLUTION::RESULT EVOLUTION::FUNCTION::CreateTextFileWrite(CORE::FILE::ITextFileWrite** pp_text_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode){
    TextFileWrite* file_write = NEW TextFileWrite();
    
    if (EVOLUTION_FAILED(file_write->Create(file_name, mode)))
    {
        file_write->Release();
        *pp_text_file_write = nullptr;
        return EVOLUTION::_RESULT::E_unknown;
    }
    *pp_text_file_write = file_write;
    return EVOLUTION::_RESULT::S_ok;
}