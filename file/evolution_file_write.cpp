#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

//IUnknown
//IUnknown
u32 FileWrite::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT FileWrite::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileWrite))
    {
        *ppvObject = static_cast<IFile*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_FileWrite))
    {
        *ppvObject = static_cast<IFileWrite*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 FileWrite::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

FileWrite::FileWrite(const c8* filename, Mode::_MODE mode){
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++){}

    switch (mode)
    {
    case Mode::_NEW:
        fopen_s(&this->mp_fp, (c8*)this->mp_file_name, "wb");
        break;
    case Mode::_APPEND:
        fopen_s(&this->mp_fp, (c8*)this->mp_file_name, "ab");
        break;
    }

    if (this->mp_fp == nullptr)
    {
        throw FIleException::FILE_READ_EXCEPTION;
    }
}

FileWrite::FileWrite(const c16* filename, Mode::_MODE mode){
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c16[file_name_length + 1];

    //strcopy
    const c16* s = filename;
    c16* d = (c16*)this->mp_file_name;
    while (*d++ = *s++){}

    switch (mode)
    {
    case Mode::_NEW:
        _wfopen_s(&this->mp_fp, (c16*) this->mp_file_name, L"wb");
        break;
    case Mode::_APPEND:
        _wfopen_s(&this->mp_fp, (c16*) this->mp_file_name, L"ab");
        break;
    }

    if (this->mp_fp == nullptr)
    {
        throw FIleException::FILE_READ_EXCEPTION;
    }
}

FileWrite::~FileWrite(){
    if (this->mp_fp)
    {
        fclose(this->mp_fp);
    }
    EVOLUTION_DELETE_ARRAY(this->mp_file_name);
}

//ファイルのサイズの取得
u64 FileWrite::GetFileSize()const{
    fpos_t now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    fpos_t file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定
void FileWrite::SetPos(const u64& index)const{
    fsetpos(this->mp_fp, (fpos_t*)&index);
}

//ファイルのポジションのを取得
u64 FileWrite::GetPos()const{
    fpos_t pos;
    fgetpos(this->mp_fp, &pos);
    return pos;
}

//ファイルの終端確認
bool FileWrite::IsEof()const{
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。
void FileWrite::Flash(){
    if (this->mp_fp){
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる
void FileWrite::Close(){
    if (this->mp_fp){
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み
s32 FileWrite::Write(void* data, u32 length){
    return fwrite(data, length, 1, this->mp_fp);
}