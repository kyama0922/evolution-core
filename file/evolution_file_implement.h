#ifndef __EVOLUTION_FILE_IMPLEMENT_H__
#define __EVOLUTION_FILE_IMPLEMENT_H__

#include "evolution_file_interface.h"

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

                FileRead(const c8* filename);
                FileRead(const c16* filename);
                ~FileRead();

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

                FileWrite(const c8* filename, Mode::_MODE mode);
                FileWrite(const c16* filename, Mode::_MODE mode);
                ~FileWrite();

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