#ifndef __EVOLUTION_FILE_INTERFACE_H__
#define __EVOLUTION_FILE_INTERFACE_H__

#include <evolution_type.h>

namespace EVOLUTION {
    namespace CORE {
        namespace FILE {

            struct FIleException {

                enum _EXCEPTION {
                    FILE_READ_EXCEPTION, //ファイルをリードできませんでした。
                };
            };

            struct Mode {

                enum _MODE {
                    _NEW_,     //新規作成します。
                    _APPEND_,  //バッファの最後に追加します。
                };
            };

            //ファイル用インターフェイス

            class IFile : public IUnknown {
                EVOLUTION_NOT_DESTRUCTOR(IFile);
            public:
                //ファイルのサイズの取得
                virtual u64 GetFileSize()const = 0;
                //ファイルのポジションのを設定
                virtual void SetPos(const u64& index)const = 0;
                //ファイルのポジションのを取得
                virtual u64 GetPos()const = 0;
                //ファイルの終端確認
                virtual bool IsEof()const = 0;
                //ファイルをフラッシュします。
                virtual void Flash() = 0;
                //ファイルを閉じる
                virtual void Close() = 0;
            };

            //読み込み用ファイルインターフェイス

            class IFileRead : public IFile {
                EVOLUTION_NOT_DESTRUCTOR(IFileRead);
            public:
                //データの読み込み
                virtual s32 Read(void* data, u32 length)const = 0;
            };

            //書き込み用ファイルインターフェイス

            class IFileWrite : public IFile {
                EVOLUTION_NOT_DESTRUCTOR(IFileWrite);
            public:
                //データの書き込み
                virtual s32 Write(void* data, u32 length) = 0;
            };

            //Text読み込み用ファイルインターフェイス

            class ITextFileRead : public IFileRead {
                EVOLUTION_NOT_DESTRUCTOR(ITextFileRead);
            public:
                //テキストを一行読み込む
                virtual s32 Gets(c8* text_buffer, u32 length)const = 0;
            };

            //Text書き込み用ファイルインターフェイス

            class ITextFileWrite : public IFileWrite {
                EVOLUTION_NOT_DESTRUCTOR(ITextFileWrite);
            public:
                //データの書き込み
                virtual s32 Puts(const c8* text) = 0;
            };
        }
    }

    namespace FUNCTION {
        EVOLUTION::RESULT CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c8* file_name);
        EVOLUTION::RESULT CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c16* file_name);
        EVOLUTION::RESULT CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode);
        EVOLUTION::RESULT CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode);

        EVOLUTION::RESULT CreateTextFileRead(CORE::FILE::ITextFileRead** pp_text_file_read, const c8* file_name);
        EVOLUTION::RESULT CreateTextFileRead(CORE::FILE::ITextFileRead** pp_text_file_read, const c16* file_name);
        EVOLUTION::RESULT CreateTextFileWrite(CORE::FILE::ITextFileWrite** pp_text_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode);
        EVOLUTION::RESULT CreateTextFileWrite(CORE::FILE::ITextFileWrite** pp_text_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode);
    }


    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID {
        // {2CA2BD10-DB50-4344-91C3-694E031E77A7}
        static const EVOLUTION_IID IID_IFile = {0x2ca2bd10, 0xdb50, 0x4344,
            { 0x91, 0xc3, 0x69, 0x4e, 0x3, 0x1e, 0x77, 0xa7}};

        // {DD292ABE-5BB3-402b-9EB0-7CE5F9A06A98}
        static const EVOLUTION_IID IID_IFileRead = {0xdd292abe, 0x5bb3, 0x402b,
            { 0x9e, 0xb0, 0x7c, 0xe5, 0xf9, 0xa0, 0x6a, 0x98}};

        // {A84DE65E-3B3F-465d-9852-1F730C1496FF}
        static const EVOLUTION_IID IID_IFileWrite = {0xa84de65e, 0x3b3f, 0x465d,
            { 0x98, 0x52, 0x1f, 0x73, 0xc, 0x14, 0x96, 0xff}};

        // {5788070A-A0C7-4993-80CF-225A962FC478}
        static const EVOLUTION_IID IID_ITextFileRead = {0x5788070a, 0xa0c7, 0x4993,
            { 0x80, 0xcf, 0x22, 0x5a, 0x96, 0x2f, 0xc4, 0x78}};

        // {594FE6A5-42C2-4f75-B6C1-D7F5BA016547}
        static const EVOLUTION_IID IID_ITextFileWrite = {0x594fe6a5, 0x42c2, 0x4f75,
            { 0xb6, 0xc1, 0xd7, 0xf5, 0xba, 0x1, 0x65, 0x47}};

    }
}
#endif