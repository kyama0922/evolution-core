#ifndef __EVOLUTION_TIMER_INTERFACE_H__
#define __EVOLUTION_TIMER_INTERFACE_H__


#include <evolution_type.h>

namespace EVOLUTION{
    namespace CORE{
        namespace TIMER{

            //��Ԃ͂��߂ɍ쐬�������Ԃ���v������܂�
            class IApplicationCounter : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IApplicationCounter);
            public:
                //�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
                virtual u64 GetMilliSecondU64()const = 0;
                //�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
                virtual u32 GetMilliSecondU32()const = 0;
            };

            //�X�g�b�v�E�H�b�`�N���X
            class IStopWatch : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IStopWatch);
            public:
                //������
                virtual void Start() = 0;
                //��~
                virtual void Stop() = 0;
                //�ꎞ��~
                virtual void Pause() = 0;
                //�ĊJ
                virtual void RePause() = 0;
                //�������Ă���
                virtual bool IsStart()const = 0;

                //���ݎ��Ԃ̎擾(millisecond)
                virtual u32 GetMilliSecondU32()const = 0;
                //���ݎ��Ԃ̎擾(second)
                virtual u32 GetSecondU32()const = 0;
            };
        }
    }

    namespace FUNCTION{
        //�쐬�������Ԃ���v������܂�
        EVOLUTION::RESULT CreateApplicationCounter(CORE::TIMER::IApplicationCounter** pp_application_counter);
        EVOLUTION::RESULT CreateStopWatch(CORE::TIMER::IStopWatch** pp_stop_watch);
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {88B5BB53-FD5D-4bc8-A5FC-429EF6AE6C64}
        static const EVOLUTION_IID IID_IApplicationCounter =
        { 0x88b5bb53, 0xfd5d, 0x4bc8, { 0xa5, 0xfc, 0x42, 0x9e, 0xf6, 0xae, 0x6c, 0x64 } };

        // {17F13AEC-87E5-4fdf-BA15-C80EE72173EC}
        static const EVOLUTION_IID IID_IStopWatch =
        { 0x17f13aec, 0x87e5, 0x4fdf, { 0xba, 0x15, 0xc8, 0xe, 0xe7, 0x21, 0x73, 0xec } };
    }

}
#endif //__EVOLUTION_TIMER_INTERFACE_H__