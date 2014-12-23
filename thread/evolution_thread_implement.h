#ifndef __EVOLUTION_THREAD_IMPLEMENT_H__
#define __EVOLUTION_THREAD_IMPLEMENT_H__

#include "evolution_thread_interface.h"
#include "../template/evolution_template.h"
#include <Windows.h>

namespace EVOLUTION{
    namespace CORE{
        namespace THREAD{
            class Parameter;
            class Result;
            class ThreadPool;
            class Mutex;
            class Thread;


            //パラメター
            class Parameter : public IParameter {
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                struct _Parameter{
                    ptr_t pointer;
                    ptr_size_t size;
                };
                u32 m_parameter_count;
                _Parameter* mp_parameter;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                Parameter();
                ~Parameter();

                //作成したパラメーター数を取得します。
                u32 GetParameterCount()const;
                //パラメーターを作成します。
                ThreadResult::_RESULT CreateParameters(u32 param_count);
                //パラメーター用メモリを確保します。
                ThreadResult::_RESULT CreateParameterMemory(u32 index, u32 param_size);
                //パラメーターサイズを取得します。
                u32 GetParameterSize(u32 index)const;
                //パラメーターに値をセットします。
                ThreadResult::_RESULT SetParameter(u32 index,const void* val, u32 param_size);
                //パラメーターを取得します。
                const void* GetParameter(u32 index)const;
            };

            class Result : public IResult{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                ptr_t m_value_pointer;
                ptr_size_t m_value_size;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                Result();
                ~Result();

                //パラメーターを作成します。
                ThreadResult::_RESULT CreateResultMemory(u32 value_size);
                //Resultの設定
                ThreadResult::_RESULT SetResult(const void* value, u32 value_size);
                //Resultの値のサイズ
                u32 GetResultSize()const;
                //Resultの取得
                void* GetResult()const;
            };

            struct THREAD_POOL_FLAG{
                enum _FLAG{
                    LOOP = 0x00000001,
                    WAIT = 0x00000002,
                    END = 0x00000004,
                };
            };

            class WorkThread{
            public:
                u16 m_pool_write_thread_read_flg;
                u16 m_pool_read_thread_write_flg;

                IResult* mp_result;
                IParameter* mp_parameter;
                ITask* mp_task;
                IMutex* mp_mutex;
                Thread* mp_thread;
                
         
                WorkThread();
                RESULT Initialise(u32 stack_size);
            };

            struct TaskInfo{
                ITask* task;
                IParameter* parameter;
            };

            class ThreadPool :public IThreadPool{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;

                //タスク用ミューテックス
                Mutex* mp_mutex;

                u32 m_stack_size;

                u32 m_flag_cout;
                u32* mp_thread_use_flag;
                WorkThread* mp_work_thread;

                u32 m_pool_count;

                //現在登録されいてるタスクの数
                u32 m_resistor_task_count;
                //タスク用キューの最大数
                u32 m_max_task_queue_count;
                TaskInfo* mp_taskinfo_queue_root;

                //
                TaskInfo* mp_taskinfo_queue_last;
                TaskInfo* mp_taskinfo_queue_first;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                ThreadPool(u32 stack_size, u32 pool_count, u32 queue_size);
                ~ThreadPool();

                u32 GetPoolCount();
                //タスクの実行
                void Execute(u32 sleep_ms_time);
                //タスクの登録(スレッドセーフ)
                ThreadResult::_RESULT TaskExecute(ITask* task, IParameter* parameter);
                //実行タスク数を取得
                s32 TaskExecuteCount()const;

                //タスクのキューに積む(スレッドセーフ)
                void PushTask(ITask* task, IParameter* parameter);
                //タスクの取得
                TaskInfo* PopTask();

                static void Thread(ptr_t argument, const IThread* thread);
            };

            class Mutex : public IMutex{
            private:
                static u16 unique_id;
                static u64 CreateUniqueId();

                tchar m_id[8];
                EVOLUTION::InstanceCounter m_instance_counter;
                HANDLE m_mutex_handle;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                Mutex();
                ~Mutex();

                HANDLE Lock()const;
                ThreadResult::_RESULT Mutex::UnLock(HANDLE lock_handle)const;
            };


            class Thread :public IThread{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                u32 m_stack_size;
                ptr_t m_argument;
                HANDLE m_thread_handle;
                HANDLE m_lock_handle;
                Mutex* mp_mutex;
                void(*m_function_pointer)(ptr_t address, const IThread* thread);

            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                Thread(u32 stack_size);
                ~Thread();

                ThreadResult::_RESULT Run(void(*function)(ptr_t argument, const IThread* thread), ptr_t argument);
                ThreadResult::_RESULT Join();
                ThreadResult::_RESULT Join(u32 time_out);
                ThreadResult::_RESULT Lock(IMutex* mutex)const;
                ThreadResult::_RESULT UnLock()const;
                bool IsRun()const;
                bool IsEnd()const;

                HANDLE GetHandle()const;
            private:
                static unsigned _stdcall Start(void* myself);
            };

        }
    }

    //-------------------------------------------------------
    //EVOLUTION Globally Unique Identifier
    //-------------------------------------------------------
    namespace EVOLUTION_GUID{
        // {3137751A-A6F8-4105-AD04-49D1A48528BF}
        static const EVOLUTION_IID IID_Parameter =
        { 0x3137751a, 0xa6f8, 0x4105, { 0xad, 0x4, 0x49, 0xd1, 0xa4, 0x85, 0x28, 0xbf } };

        // {644A19C0-7BB3-4b6b-BAAC-EF798FD70CD8}
        static const EVOLUTION_IID IID_Result =
        { 0x644a19c0, 0x7bb3, 0x4b6b, { 0xba, 0xac, 0xef, 0x79, 0x8f, 0xd7, 0xc, 0xd8 } };

        // {34E977C2-5E92-4d99-95D9-DAF462765CC7}
        static const EVOLUTION_IID IID_ThreadPool =
        { 0x34e977c2, 0x5e92, 0x4d99, { 0x95, 0xd9, 0xda, 0xf4, 0x62, 0x76, 0x5c, 0xc7 } };


        // {AF2CA453-A262-4520-BEBB-FA414FF72979}
        static const EVOLUTION_IID IID_Mutex =
        { 0xaf2ca453, 0xa262, 0x4520, { 0xbe, 0xbb, 0xfa, 0x41, 0x4f, 0xf7, 0x29, 0x79 } };


        // {EDADF378-FF4A-41e0-9A84-EC5DA330C69C}
        static const EVOLUTION_IID IID_Thread =
        { 0xedadf378, 0xff4a, 0x41e0, { 0x9a, 0x84, 0xec, 0x5d, 0xa3, 0x30, 0xc6, 0x9c } };

    }

}
#endif //__EVOLUTION_THREAD_INTERFACE_H__