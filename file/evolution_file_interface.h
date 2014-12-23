#ifndef __EVOLUTION_FILE_INTERFACE_H__
#define __EVOLUTION_FILE_INTERFACE_H__

#include <evolution.h>

namespace EVOLUTION{
    namespace CORE{
        namespace FILE{


            struct FIleException{
                enum _EXCEPTION{
                    FILE_READ_EXCEPTION,//�t�@�C�������[�h�ł��܂���ł����B
                };
            };

            struct Mode{
                enum _MODE{
                    _NEW , //�V�K�쐬���܂��B
                    _APPEND,//�o�b�t�@�̍Ō�ɒǉ����܂��B
                };
            };

            //�t�@�C���p�C���^�[�t�F�C�X
            class IFile : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IFile);
            public:
                //�t�@�C���̃T�C�Y�̎擾
                virtual u64 GetFileSize()const = 0;
                //�t�@�C���̃|�W�V�����̂�ݒ�
                virtual void SetPos(const u64& index)const = 0;
                //�t�@�C���̃|�W�V�����̂��擾
                virtual u64 GetPos()const = 0;
                //�t�@�C���̏I�[�m�F
                virtual bool IsEof()const = 0;
                //�t�@�C�����t���b�V�����܂��B
                virtual void Flash() = 0;
                //�t�@�C�������
                virtual void Close() = 0;
            };

            //�ǂݍ��ݗp�t�@�C���C���^�[�t�F�C�X
            class IFileRead : public IFile{
                EVOLUTION_NOT_DESTRUCTOR(IFileRead);
            public:
                //�f�[�^�̓ǂݍ���
                virtual s32 Read(void* data, u32 length)const = 0;
            };

            //�������ݗp�t�@�C���C���^�[�t�F�C�X
            class IFileWrite : public IFile{
                EVOLUTION_NOT_DESTRUCTOR(IFileWrite);
            public:
                //�f�[�^�̏�������
                virtual  s32 Write(void* data, u32 length)= 0;
            };
        }
    }

    namespace FUNCTION{
        EVOLUTION::RESULT CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c8* file_name);
        EVOLUTION::RESULT CreateFileRead(CORE::FILE::IFileRead** pp_file_read, const c16* file_name);
        EVOLUTION::RESULT CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c8* file_name, CORE::FILE::Mode::_MODE mode);
        EVOLUTION::RESULT CreateFileWrite(CORE::FILE::IFileWrite** pp_file_write, const c16* file_name, CORE::FILE::Mode::_MODE mode);
    }


    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {2CA2BD10-DB50-4344-91C3-694E031E77A7}
        static const EVOLUTION_IID IID_IFile =
        { 0x2ca2bd10, 0xdb50, 0x4344, { 0x91, 0xc3, 0x69, 0x4e, 0x3, 0x1e, 0x77, 0xa7 } };

        // {DD292ABE-5BB3-402b-9EB0-7CE5F9A06A98}
        static const EVOLUTION_IID IID_IFileRead =
        { 0xdd292abe, 0x5bb3, 0x402b, { 0x9e, 0xb0, 0x7c, 0xe5, 0xf9, 0xa0, 0x6a, 0x98 } };

        // {A84DE65E-3B3F-465d-9852-1F730C1496FF}
        static const EVOLUTION_IID IID_IFileWrite =
        { 0xa84de65e, 0x3b3f, 0x465d, { 0x98, 0x52, 0x1f, 0x73, 0xc, 0x14, 0x96, 0xff } };

    }
}
#endif