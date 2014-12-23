#ifndef __EVOLUTION_FILE_IMPLEMENT_H__
#define __EVOLUTION_FILE_IMPLEMENT_H__

#include "evolution_file_interface.h"

namespace EVOLUTION{
    namespace CORE{
        namespace FILE{

            //読み込み用ファイルインターフェイス
            class FileRead : public IFileRead{
            public:
                EVOLUTION::InstanceCounter m_instance_counter;
                void* mp_file_name;
                ::FILE* mp_fp;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                FileRead(const c8* filename);
                FileRead(const c16* filename);
                ~FileRead();

                //ファイルのサイズの取得
                u64 GetFileSize()const;
                //ファイルのポジションのを設定
                void SetPos(const u64& index)const;
                //ファイルのポジションのを取得
                u64 GetPos()const;
                //ファイルの終端確認
                bool IsEof()const;
                //ファイルをフラッシュします。
                void Flash();
                //ファイルを閉じる
                void Close();
                //データの読み込み
                s32 Read(void* data, u32 length)const;
            };

            //書き込み用ファイルインターフェイス
            class FileWrite : public IFileWrite{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                void* mp_file_name;
                ::FILE* mp_fp;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                FileWrite(const c8* filename, Mode::_MODE mode);
                FileWrite(const c16* filename, Mode::_MODE mode);
                ~FileWrite();

                //ファイルのサイズの取得
                u64 GetFileSize()const;
                //ファイルのポジションのを設定
                void SetPos(const u64& index)const;
                //ファイルのポジションのを取得
                u64 GetPos()const;
                //ファイルの終端確認
                bool IsEof()const;
                //ファイルをフラッシュします。
                void Flash();
                //ファイルを閉じる
                void Close();
                //データの書き込み
                s32 Write(void* data, u32 length);
            };
        }
    }
    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {6D3C1C63-7F87-4f45-90EB-17D77D159F41}
        static const EVOLUTION_IID IID_FileRead =
        { 0x6d3c1c63, 0x7f87, 0x4f45, { 0x90, 0xeb, 0x17, 0xd7, 0x7d, 0x15, 0x9f, 0x41 } };

        // {A93A27B7-4C5F-4649-85EF-CF65C166C8A1}
        static const EVOLUTION_IID IID_FileWrite =
        { 0xa93a27b7, 0x4c5f, 0x4649, { 0x85, 0xef, 0xcf, 0x65, 0xc1, 0x66, 0xc8, 0xa1 } };
    }
}
#endif//!__EVOLUTION_FILE_IMPLEMENT_H__