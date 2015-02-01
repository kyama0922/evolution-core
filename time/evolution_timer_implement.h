#ifndef __EVOLUTION_TIMER_IMPLEMENT_H__
#define __EVOLUTION_TIMER_IMPLEMENT_H__


#include "evolution_timer_interface.h"
#include <sys/time.h>

namespace EVOLUTION {
    namespace CORE {
        namespace TIMER {

            //アプリケーションがスタートしてからの時間

            class HighQualityApplicationCounter : public IApplicationCounter {
            private:
                EVOLUTION::InstanceCounter m_instance_counter;

                timeval m_start;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                HighQualityApplicationCounter();
                ~HighQualityApplicationCounter();

                RESULT Create();

                //アプリケーションが開始してからの経過時間
                u64 GetMilliSecondU64()const;
                //アプリケーションが開始してからの経過時間
                u32 GetMilliSecondU32()const;
            };

            //アプリケーションがスタートしてからの時間

            class ApplicationCounter : public IApplicationCounter {
            private:
                EVOLUTION::InstanceCounter m_instance_counter;

                timeval m_start;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                ApplicationCounter();
                ~ApplicationCounter();

                RESULT Create();

                //アプリケーションが開始してからの経過時間
                u64 GetMilliSecondU64()const;
                //アプリケーションが開始してからの経過時間
                u32 GetMilliSecondU32()const;
            };

            //ストップウォッチクラス

            class StopWatch : public IStopWatch {
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                u32 m_start_time;
                u32 m_stop_time;
                bool m_start;

                IApplicationCounter* mp_application_counter;

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                StopWatch();
                ~StopWatch();

                RESULT Create();


                //動かす
                void Start();
                //停止
                void Stop();
                //一時停止
                void Pause();
                //再開
                void RePause();
                //動かしている
                bool IsStart()const;

                //現在時間の取得(millisecond)
                u32 GetMilliSecondU32()const;
                //現在時間の取得(second)
                u32 GetSecondU32()const;
            };
        }
    }
    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID {
        // {1829B87D-2030-4094-8BA5-584AA279AC44}
        static const EVOLUTION_IID IID_HighQualityApplicationCounter = {0x1829b87d, 0x2030, 0x4094,
            { 0x8b, 0xa5, 0x58, 0x4a, 0xa2, 0x79, 0xac, 0x44}};


        // {DDDE664B-B647-4366-834F-9CE89DF0386B}
        static const EVOLUTION_IID IID_ApplicationCounter = {0xddde664b, 0xb647, 0x4366,
            { 0x83, 0x4f, 0x9c, 0xe8, 0x9d, 0xf0, 0x38, 0x6b}};

        // {51BB0CBB-40D5-4bee-BCCF-F96DF66D6910}
        static const EVOLUTION_IID IID_StopWatch = {0x51bb0cbb, 0x40d5, 0x4bee,
            { 0xbc, 0xcf, 0xf9, 0x6d, 0xf6, 0x6d, 0x69, 0x10}};
    }

}
#endif //__EVOLUTION_TIMER_IMPLEMENT_H__