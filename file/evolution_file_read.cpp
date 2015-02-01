#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

//IUnknown

u32 FileRead::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT FileRead::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFile)) {
        *ppvObject = static_cast<IFile*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileRead)) {
        *ppvObject = static_cast<IFileRead*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_FileRead)) {
        *ppvObject = static_cast<FileRead*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 FileRead::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

FileRead::FileRead() : mp_fp(nullptr) {

}

FileRead::~FileRead() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    c8* ptr = (c8*)this->mp_file_name;
    this->mp_file_name = nullptr;
    EVOLUTION_DELETE_ARRAY(ptr);
}

RESULT FileRead::Create(const c8* filename) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++) {
    }

    this->mp_fp = fopen((c8*) this->mp_file_name, "rb");
    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

RESULT FileRead::Create(const c16* filename) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    wcstombs((c8*)this->mp_file_name, filename, file_name_length);
    this->mp_fp = fopen((c8*) this->mp_file_name, "rb");

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }


    return _RESULT::S_ok;
}

//ファイルのサイズの取得

u64 FileRead::GetFileSize()const {
    u64 now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    u64 file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定

void FileRead::SetPos(const u64& index)const {
    fpos64_t pos;
    pos.__pos = index;
    fsetpos64(this->mp_fp, (fpos64_t*) & pos);
}

//ファイルのポジションのを取得

u64 FileRead::GetPos()const {
    fpos64_t pos;
    fgetpos64(this->mp_fp, &pos);
    return pos.__pos;
}

//ファイルの終端確認

bool FileRead::IsEof()const {
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。

void FileRead::Flash() {
    if (this->mp_fp) {
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる

void FileRead::Close() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み

s32 FileRead::Read(void* data, u32 length)const {
    return fread(data, 1, length, this->mp_fp);
}

//---------------------------------------------
//          TextFileRead
//---------------------------------------------

//IUnknown

u32 TextFileRead::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT TextFileRead::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFile)) {
        *ppvObject = static_cast<IFile*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileRead)) {
        *ppvObject = static_cast<IFileRead*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_TextFileRead)) {
        *ppvObject = static_cast<TextFileRead*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 TextFileRead::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

TextFileRead::TextFileRead() : mp_fp(nullptr) {

}

TextFileRead::~TextFileRead() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    c8* ptr = (c8*)this->mp_file_name;
    this->mp_file_name = nullptr;
    EVOLUTION_DELETE_ARRAY(ptr);
}

RESULT TextFileRead::Create(const c8* filename) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++) {
    }

    this->mp_fp = fopen((c8*) this->mp_file_name, "r");


    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

RESULT TextFileRead::Create(const c16* filename) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    wcstombs((c8*)this->mp_file_name, filename, file_name_length);
    this->mp_fp = fopen((c8*) this->mp_file_name, "r");

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

//ファイルのサイズの取得

u64 TextFileRead::GetFileSize()const {
    u64 now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    u64 file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定

void TextFileRead::SetPos(const u64& index)const {
    fpos64_t pos;
    pos.__pos = index;
    fsetpos64(this->mp_fp, (fpos64_t*) & pos);
}

//ファイルのポジションのを取得

u64 TextFileRead::GetPos()const {
    fpos64_t pos;
    fgetpos64(this->mp_fp, &pos);
    return pos.__pos;
}

//ファイルの終端確認

bool TextFileRead::IsEof()const {
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。

void TextFileRead::Flash() {
    if (this->mp_fp) {
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる

void TextFileRead::Close() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み

s32 TextFileRead::Read(void* data, u32 length)const {
    return fread(data, 1, length, this->mp_fp);
}

s32 TextFileRead::Gets(c8* text_buffer, u32 length)const {
    c8* buffer = fgets(text_buffer, length, this->mp_fp);
    return (buffer != nullptr) ? strlen(buffer) : 0;
}