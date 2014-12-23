#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

//IUnknown
//IUnknown
u32 FileRead::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT FileRead::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileRead))
    {
        *ppvObject = static_cast<IFile*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_FileRead))
    {
        *ppvObject = static_cast<IFileRead*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 FileRead::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

FileRead::FileRead(const c8* filename){
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++){}
    
    fopen_s(&this->mp_fp, (c8*) this->mp_file_name, "rb");
    if (this->mp_fp == nullptr)
    {
        throw FIleException::FILE_READ_EXCEPTION;
    }
}

FileRead::FileRead(const c16* filename){
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c16* s = filename;
    c16* d = (c16*)this->mp_file_name;
    while (*d++ = *s++){}
    _wfopen_s(&this->mp_fp, (c16*) this->mp_file_name, L"rb");
    if (this->mp_fp == nullptr)
    {
        throw FIleException::FILE_READ_EXCEPTION;
    }
}
FileRead::~FileRead(){
    if (this->mp_fp)
    {
        fclose(this->mp_fp);
    }
    EVOLUTION_DELETE_ARRAY(this->mp_file_name);
}

//ファイルのサイズの取得
u64 FileRead::GetFileSize()const{
    fpos_t now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    fpos_t file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定
void FileRead::SetPos(const u64& index)const{
    fsetpos(this->mp_fp, (fpos_t*)&index);
}

//ファイルのポジションのを取得
u64 FileRead::GetPos()const{
    fpos_t pos;
    fgetpos(this->mp_fp, &pos);
    return pos;
}

//ファイルの終端確認
bool FileRead::IsEof()const{
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。
void FileRead::Flash(){
    if (this->mp_fp){
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる
void FileRead::Close(){
    if (this->mp_fp){
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み
s32 FileRead::Read(void* data, u32 length)const{
    return fread(data, 1, length, this->mp_fp);
}