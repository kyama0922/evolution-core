#ifndef __EVOLUTION_THREAD_INTERFACE_H__
#define __EVOLUTION_THREAD_INTERFACE_H__

#include <evolution_type.h>

#include "evolution_thread_result.h"

namespace EVOLUTION{
    namespace CORE{
        namespace THREAD{

            //�p�����^�[
            class IParameter : public IUnknown {
                EVOLUTION_NOT_DESTRUCTOR(IParameter);
            public:
                //�쐬�����p�����[�^�[�����擾���܂��B
                virtual u32 GetParameterCount()const = 0;
                //�p�����[�^�[���쐬���܂��B
                virtual ThreadResult::_RESULT CreateParameters(u32 param_count) = 0;
                //�p�����[�^�[�p���������m�ۂ��܂��B
                virtual ThreadResult::_RESULT CreateParameterMemory(u32 index, u32 param_size) = 0;
                //�p�����[�^�[�T�C�Y���擾���܂��B
                virtual u32 GetParameterSize(u32 index)const = 0;
                //�p�����[�^�[�ɒl���Z�b�g���܂��B
                virtual ThreadResult::_RESULT SetParameter(u32 index, const void* val, u32 param_size) = 0;
                //�p�����[�^�[���擾���܂��B
                virtual const void* GetParameter(u32 index)const = 0;
            };

            class IResult : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IResult);
            public:
                virtual ThreadResult::_RESULT CreateResultMemory(u32 value_size) = 0;
                //Result�̐ݒ�
                virtual ThreadResult::_RESULT SetResult(const void* value, u32 value_size) = 0;
                //Result�̒l�̃T�C�Y
                virtual u32 GetResultSize()const = 0;
                //Result�̎擾
                virtual void* GetResult()const = 0;
            };

            class ITask{
            public:
                //���s
                virtual void Execute(const IParameter* parameter, IResult* result) = 0;
                //�^�X�N���I�������ThreadPool����Ăяo���܂��B
                virtual void OnEndExecute(const IResult* result) = 0;
            };

            class IThreadPool :public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IThreadPool);
            public:
                //�^�X�N�̎��s(�~���b)
                virtual void Execute(u32 sleep_ms_time) = 0;
                //�^�X�N�̓o�^(�X���b�h�Z�[�t)
                virtual ThreadResult::_RESULT TaskExecute(ITask* task, IParameter* parameter) = 0;
                //���s�^�X�N�����擾
                virtual s32 TaskExecuteCount()const = 0;
            };


            //Semaphore�N���X
            class ISemaphore :public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(ISemaphore);
            public:
            };

            //Mutex�N���X
            class IMutex :public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IMutex);
            public:
                
            };

            //�X���b�h�N���X
            class IThread :public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IThread);
            public:
                //�ʃX���b�h�Ŏ��s���܂��B
                virtual ThreadResult::_RESULT Run(void(*function)(ptr_t address ,const IThread* thread), ptr_t address) = 0;
                //�X���b�h���I������܂ŌĂяo�����̃X���b�h���u���b�N���܂�
                virtual ThreadResult::_RESULT Join() = 0;
                //�X���b�h���I������܂ŌĂяo�����̃X���b�h���u���b�N���܂�(�^�C���A�E�g���ݒ�ł��܂��B(ms))
                virtual ThreadResult::_RESULT Join(u32 time_out) = 0;
                //�X���b�h�����b�N���܂��B
                virtual ThreadResult::_RESULT Lock(IMutex* mutex)const = 0;
                //�X���b�h���A�����b�N���܂��B
                virtual ThreadResult::_RESULT UnLock()const = 0;
                //�X���b�h�����s��Ԃɂ��邩���ׂ܂��B
                virtual bool IsRun()const = 0;
                //�X���b�h���I����Ԃɂ��邩�ǂ����B
                virtual bool IsEnd()const = 0;
            };

        }
    }

    namespace FUNCTION{
        EVOLUTION::RESULT CreateThread(CORE::THREAD::IThread** pp_thread, u32 stack_size);
        EVOLUTION::RESULT CreateThreadMutex(CORE::THREAD::IMutex** pp_mutex);
        EVOLUTION::RESULT CreateThreadPool(CORE::THREAD::IThreadPool** pp_thread_pool, u32 stack_size, u32 pool_count, u32 queue_size);
        EVOLUTION::RESULT CreateParameter(CORE::THREAD::IParameter** pp_parameter);
        EVOLUTION::RESULT CreateResult(CORE::THREAD::IResult** pp_result);
    }


    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {661AA596-59F5-4962-9F57-35215D506E30}
        static const EVOLUTION_IID IID_IParameter =
        { 0x661aa596, 0x59f5, 0x4962, { 0x9f, 0x57, 0x35, 0x21, 0x5d, 0x50, 0x6e, 0x30 } };


        // {00C3C3C1-508E-4ff0-82E7-CD41F7D0D0F2}
        static const EVOLUTION_IID IID_IResult =
        { 0xc3c3c1, 0x508e, 0x4ff0, { 0x82, 0xe7, 0xcd, 0x41, 0xf7, 0xd0, 0xd0, 0xf2 } };


        // {61FEC7DA-D521-4446-9633-950A474A13B7}
        static const EVOLUTION_IID IID_IThreadPool =
        { 0x61fec7da, 0xd521, 0x4446, { 0x96, 0x33, 0x95, 0xa, 0x47, 0x4a, 0x13, 0xb7 } };

        // {DDDA6908-B04C-49e6-98EA-0294D6510C0D}
        static const EVOLUTION_IID IID_ISemaphore =
        { 0xddda6908, 0xb04c, 0x49e6, { 0x98, 0xea, 0x2, 0x94, 0xd6, 0x51, 0xc, 0xd } };


        // {70E48208-641C-4712-B02B-3D9173CCD399}
        static const EVOLUTION_IID IID_IMutex =
        { 0x70e48208, 0x641c, 0x4712, { 0xb0, 0x2b, 0x3d, 0x91, 0x73, 0xcc, 0xd3, 0x99 } };

        // {98D2FC82-1165-4112-B2B8-DE2AEB7E9361}
        static const EVOLUTION_IID IID_IThread =
        { 0x98d2fc82, 0x1165, 0x4112, { 0xb2, 0xb8, 0xde, 0x2a, 0xeb, 0x7e, 0x93, 0x61 } };
    }


}
#endif //__EVOLUTION_THREAD_INTERFACE_H__