#ifndef __EVOLUTION_FILE_IMPLEMENT_H__
#define __EVOLUTION_FILE_IMPLEMENT_H__

#include "evolution_file_interface.h"
#include "../function/evolution_function.h"

namespace EVOLUTION{
    namespace CORE{
        namespace FILE{

            //�ǂݍ��ݗp�t�@�C���C���^�[�t�F�C�X
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

                FileRead();
                ~FileRead();

                RESULT Create(const c8* filename);
                RESULT Create(const c16* filename);

                //�t�@�C���̃T�C�Y�̎擾
                u64 GetFileSize()const;
                //�t�@�C���̃|�W�V�����̂�ݒ�
                void SetPos(const u64& index)const;
                //�t�@�C���̃|�W�V�����̂��擾
                u64 GetPos()const;
                //�t�@�C���̏I�[�m�F
                bool IsEof()const;
                //�t�@�C�����t���b�V�����܂��B
                void Flash();
                //�t�@�C�������
                void Close();
                //�f�[�^�̓ǂݍ���
                s32 Read(void* data, u32 length)const;
            };

            //Text�ǂݍ��ݗp�t�@�C���C���^�[�t�F�C�X
            class TextFileRead : public ITextFileRead{
            public:
                EVOLUTION::InstanceCounter m_instance_counter;
                void* mp_file_name;
                ::FILE* mp_fp;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                TextFileRead();
                ~TextFileRead();

                RESULT Create(const c8* filename);
                RESULT Create(const c16* filename);

                //�t�@�C���̃T�C�Y�̎擾
                u64 GetFileSize()const;
                //�t�@�C���̃|�W�V�����̂�ݒ�
                void SetPos(const u64& index)const;
                //�t�@�C���̃|�W�V�����̂��擾
                u64 GetPos()const;
                //�t�@�C���̏I�[�m�F
                bool IsEof()const;
                //�t�@�C�����t���b�V�����܂��B
                void Flash();
                //�t�@�C�������
                void Close();
                //�f�[�^�̓ǂݍ���
                s32 Read(void* data, u32 length)const;

                s32 Gets(c8* text_buffer, u32 length)const;
            };

            //�������ݗp�t�@�C���C���^�[�t�F�C�X
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

                FileWrite();
                ~FileWrite();

                RESULT Create(const c8* filename, Mode::_MODE mode);
                RESULT Create(const c16* filename, Mode::_MODE mode);

                //�t�@�C���̃T�C�Y�̎擾
                u64 GetFileSize()const;
                //�t�@�C���̃|�W�V�����̂�ݒ�
                void SetPos(const u64& index)const;
                //�t�@�C���̃|�W�V�����̂��擾
                u64 GetPos()const;
                //�t�@�C���̏I�[�m�F
                bool IsEof()const;
                //�t�@�C�����t���b�V�����܂��B
                void Flash();
                //�t�@�C�������
                void Close();
                //�f�[�^�̏�������
                s32 Write(void* data, u32 length);
            };

            //Text�������ݗp�t�@�C���C���^�[�t�F�C�X
            class TextFileWrite : public ITextFileWrite{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                void* mp_file_name;
                ::FILE* mp_fp;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                TextFileWrite();
                ~TextFileWrite();

                RESULT Create(const c8* filename, Mode::_MODE mode);
                RESULT Create(const c16* filename, Mode::_MODE mode);

                //�t�@�C���̃T�C�Y�̎擾
                u64 GetFileSize()const;
                //�t�@�C���̃|�W�V�����̂�ݒ�
                void SetPos(const u64& index)const;
                //�t�@�C���̃|�W�V�����̂��擾
                u64 GetPos()const;
                //�t�@�C���̏I�[�m�F
                bool IsEof()const;
                //�t�@�C�����t���b�V�����܂��B
                void Flash();
                //�t�@�C�������
                void Close();
                //�f�[�^�̏�������
                s32 Write(void* data, u32 length);

                s32 Puts(const c8* text);
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

        // {8171018D-7F49-4c91-9C6C-D32F6535A535}
        static const EVOLUTION_IID IID_TextFileRead =
        { 0x8171018d, 0x7f49, 0x4c91, { 0x9c, 0x6c, 0xd3, 0x2f, 0x65, 0x35, 0xa5, 0x35 } };

        // {A93A27B7-4C5F-4649-85EF-CF65C166C8A1}
        static const EVOLUTION_IID IID_FileWrite =
        { 0xa93a27b7, 0x4c5f, 0x4649, { 0x85, 0xef, 0xcf, 0x65, 0xc1, 0x66, 0xc8, 0xa1 } };

        // {D5C80D02-023F-45d1-B02A-24D49CFC4E18}
        static const EVOLUTION_IID IID_TextFileWrite =
        { 0xd5c80d02, 0x23f, 0x45d1, { 0xb0, 0x2a, 0x24, 0xd4, 0x9c, 0xfc, 0x4e, 0x18 } };
    }
}
#endif//!__EVOLUTION_FILE_IMPLEMENT_H__