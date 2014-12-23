#ifndef __EVOLUTION_TIMER_IMPLEMENT_H__
#define __EVOLUTION_TIMER_IMPLEMENT_H__


#include "evolution_timer_interface.h"
#include <Windows.h>
namespace EVOLUTION{
    namespace CORE{
        namespace TIMER{

            //�A�v���P�[�V�������X�^�[�g���Ă���̎���
            class ApplicationCounter : public IApplicationCounter{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;

                LARGE_INTEGER m_clock;
                LARGE_INTEGER m_start;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                ApplicationCounter();
                ~ApplicationCounter();

                RESULT Create();

                //�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
                u64 GetMilliSecondU64()const;
                //�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
                u32 GetMilliSecondU32()const;
            };

            //�X�g�b�v�E�H�b�`�N���X
            class StopWatch : public IStopWatch{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                u32 m_start_time;
                u32 m_stop_time;
                bool m_start;

                static IApplicationCounter* sp_app_counter;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                StopWatch();
                ~StopWatch();

                RESULT Create();


                //������
                void Start();
                //��~
                void Stop();
                //�ꎞ��~
                void Pause();
                //�ĊJ
                void RePause();
                //�������Ă���
                bool IsStart()const;
                
                //���ݎ��Ԃ̎擾(millisecond)
                u32 GetMilliSecondU32()const;
                //���ݎ��Ԃ̎擾(second)
                u32 GetSecondU32()const;
            };
        }
    }
    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {DDDE664B-B647-4366-834F-9CE89DF0386B}
        static const EVOLUTION_IID IID_ApplicationCounter =
        { 0xddde664b, 0xb647, 0x4366, { 0x83, 0x4f, 0x9c, 0xe8, 0x9d, 0xf0, 0x38, 0x6b } };

        // {51BB0CBB-40D5-4bee-BCCF-F96DF66D6910}
        static const EVOLUTION_IID IID_StopWatch =
        { 0x51bb0cbb, 0x40d5, 0x4bee, { 0xbc, 0xcf, 0xf9, 0x6d, 0xf6, 0x6d, 0x69, 0x10 } };
    }

}
#endif //__EVOLUTION_TIMER_IMPLEMENT_H__