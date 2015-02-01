#include "evolution_file_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::FILE;

//IUnknown

u32 FileWrite::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT FileWrite::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFile)) {
        *ppvObject = static_cast<IFile*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileWrite)) {
        *ppvObject = static_cast<IFileWrite*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_FileWrite)) {
        *ppvObject = static_cast<FileWrite*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 FileWrite::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

FileWrite::FileWrite() : mp_fp(nullptr), mp_file_name(nullptr) {

}

FileWrite::~FileWrite() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    c8* ptr = (c8*)this->mp_file_name;
    this->mp_file_name = nullptr;
    EVOLUTION_DELETE_ARRAY(ptr);
}

RESULT FileWrite::Create(const c8* filename, Mode::_MODE mode) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++) {
    }

    switch (mode) {
        case Mode::_NEW_:
            this->mp_fp = fopen((c8*)this->mp_file_name, "wb");
            break;
        case Mode::_APPEND_:
            this->mp_fp = fopen((c8*)this->mp_file_name, "ab");
            break;
    }

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

RESULT FileWrite::Create(const c16* filename, Mode::_MODE mode) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    wcstombs((c8*)this->mp_file_name, filename, file_name_length);

    switch (mode) {
        case Mode::_NEW_:
            this->mp_fp = fopen((c8*) this->mp_file_name, "wb");
            break;
        case Mode::_APPEND_:
            this->mp_fp = fopen((c8*) this->mp_file_name, "ab");
            break;
    }

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

//ファイルのサイズの取得

u64 FileWrite::GetFileSize()const {
    u64 now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    u64 file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定

void FileWrite::SetPos(const u64& index)const {
    fpos64_t pos;
    pos.__pos = index;
    fsetpos64(this->mp_fp, (fpos64_t*) & pos);
}

//ファイルのポジションのを取得

u64 FileWrite::GetPos()const {
    fpos64_t pos;
    fgetpos64(this->mp_fp, &pos);
    return pos.__pos;
}

//ファイルの終端確認

bool FileWrite::IsEof()const {
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。

void FileWrite::Flash() {
    if (this->mp_fp) {
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる

void FileWrite::Close() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み

s32 FileWrite::Write(void* data, u32 length) {
    return fwrite(data, length, 1, this->mp_fp);
}

//---------------------------------------------
//          TextFileRead
//---------------------------------------------
//IUnknown

u32 TextFileWrite::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT TextFileWrite::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFile)) {
        *ppvObject = static_cast<IFile*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IFileWrite)) {
        *ppvObject = static_cast<IFileWrite*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_TextFileWrite)) {
        *ppvObject = static_cast<TextFileWrite*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 TextFileWrite::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

TextFileWrite::TextFileWrite() : mp_fp(nullptr), mp_file_name(nullptr) {

}

TextFileWrite::~TextFileWrite() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    c8* ptr = (c8*)this->mp_file_name;
    this->mp_file_name = nullptr;
    EVOLUTION_DELETE_ARRAY(ptr);
}

RESULT TextFileWrite::Create(const c8* filename, Mode::_MODE mode) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    //strcopy
    const c8* s = filename;
    c8* d = (c8*)this->mp_file_name;
    while (*d++ = *s++) {
    }

    switch (mode) {
        case Mode::_NEW_:
            this->mp_fp = fopen((c8*)this->mp_file_name, "w");
            break;
        case Mode::_APPEND_:
            this->mp_fp = fopen((c8*)this->mp_file_name, "a");
            break;
    }

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

RESULT TextFileWrite::Create(const c16* filename, Mode::_MODE mode) {
    u32 file_name_length = FUNCTION::Strlen(filename);
    this->mp_file_name = new c8[file_name_length + 1];

    wcstombs((c8*)this->mp_file_name, filename, file_name_length);

    switch (mode) {
        case Mode::_NEW_:
            this->mp_fp = fopen((c8*) this->mp_file_name, "w");
            break;
        case Mode::_APPEND_:
            this->mp_fp = fopen((c8*) this->mp_file_name, "a");
            break;
    }

    if (this->mp_fp == nullptr) {
        return _RESULT::E_unknown;
    }
    return _RESULT::S_ok;
}

//ファイルのサイズの取得

u64 TextFileWrite::GetFileSize()const {
    u64 now_pos = this->GetPos();
    fseek(this->mp_fp, 0, SEEK_END);
    u64 file_size = this->GetPos();
    this->SetPos(now_pos);
    return file_size;
}

//ファイルのポジションのを設定

void TextFileWrite::SetPos(const u64& index)const {
    fpos64_t pos;
    pos.__pos = index;
    fsetpos64(this->mp_fp, (fpos64_t*) & pos);
}

//ファイルのポジションのを取得

u64 TextFileWrite::GetPos()const {
    fpos64_t pos;
    fgetpos64(this->mp_fp, &pos);
    return pos.__pos;
}

//ファイルの終端確認

bool TextFileWrite::IsEof()const {
    return feof(this->mp_fp) == 0;
}

//ファイルをフラッシュします。

void TextFileWrite::Flash() {
    if (this->mp_fp) {
        fflush(this->mp_fp);
    }
}

//ファイルを閉じる

void TextFileWrite::Close() {
    if (this->mp_fp) {
        fclose(this->mp_fp);
    }
    this->mp_fp = nullptr;
}

//データの読み込み

s32 TextFileWrite::Write(void* data, u32 length) {
    return fwrite(data, length, 1, this->mp_fp);
}

s32 TextFileWrite::Puts(const c8* text) {
    return fputs(text, this->mp_fp);
}