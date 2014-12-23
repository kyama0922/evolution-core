#include "evolution_thread_implement.h"
#include "../function/evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;


//IUnknown
u32 ThreadPool::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT ThreadPool::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IThreadPool))
    {
        *ppvObject = static_cast<IThreadPool*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ThreadPool))
    {
        *ppvObject = static_cast<ThreadPool*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 ThreadPool::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}


ThreadPool::ThreadPool(u32 stack_size, u32 pool_count, u32 queue_size) :
mp_mutex(nullptr),
m_stack_size(stack_size),
m_flag_cout(0),
mp_thread_use_flag(nullptr),
mp_work_thread(nullptr),
m_pool_count(pool_count),
m_resistor_task_count(0),
m_max_task_queue_count(queue_size),
mp_taskinfo_queue_root(nullptr),
mp_taskinfo_queue_last(nullptr),
mp_taskinfo_queue_first(nullptr)
{
    
    this->mp_taskinfo_queue_root = NEW TaskInfo[queue_size];
    this->mp_taskinfo_queue_last = this->mp_taskinfo_queue_root;
    this->mp_taskinfo_queue_first = this->mp_taskinfo_queue_root;

    //�X���b�h��Ԃ�������
    this->m_flag_cout = (pool_count / (sizeof(u32) * 8)) + 1;
    this->mp_thread_use_flag = NEW u32[this->m_flag_cout];

    for (u32 i = 0; i < this->m_flag_cout; i++)
    {
        this->mp_thread_use_flag[i] = 0;
    }

    EVOLUTION::FUNCTION::CreateThreadMutex((IMutex**)&this->mp_mutex);

    this->mp_work_thread = NEW WorkThread[pool_count];
    for (u32 i = 0; i < this->m_pool_count; i++)
    {
        this->mp_work_thread[i].Initialise(this->m_stack_size);

        EVOLUTION_ENABLE_STATE(this->mp_work_thread[i].m_pool_write_thread_read_flg, THREAD_POOL_FLAG::LOOP);
        this->mp_work_thread[i].mp_thread->Run(ThreadPool::Thread, (ptr_t)&this->mp_work_thread[i]);
    }
}

ThreadPool::~ThreadPool(){
    for (u32 i = 0; i < this->m_pool_count; i++)
    {
        WorkThread* workthread = &this->mp_work_thread[i];
        //�T�X�y���h������
        EVOLUTION_DISABLED_STATE(workthread->m_pool_write_thread_read_flg, THREAD_POOL_FLAG::LOOP);
        ::ResumeThread(workthread->mp_thread->GetHandle());
     
    }

    for (u32 i = 0; i < this->m_pool_count; i++)
    {
        WorkThread* workthread = &this->mp_work_thread[i];
        workthread->mp_thread->Join();
        EVOLUTION_RELEASE(workthread->mp_result);
        EVOLUTION_RELEASE(workthread->mp_mutex);
        EVOLUTION_RELEASE(workthread->mp_thread);
    }


    EVOLUTION_RELEASE(this->mp_mutex);

    EVOLUTION_DELETE_ARRAY(this->mp_work_thread);
    EVOLUTION_DELETE_ARRAY(this->mp_thread_use_flag);
    EVOLUTION_DELETE_ARRAY(this->mp_taskinfo_queue_root);
}

u32 ThreadPool::GetPoolCount(){
    return this->m_pool_count;
}

u32 DisableBitNumber(u32 flag){
    for (s32 g = 0; g < 4; g++)
    {
        u8 bit = (u8)((flag >> (8 * g)) & 0xFF);
        if (EVOLUTION::FUNCTION::BitCount8(bit) != 8)
        {
            for (s32 j = 0; j < 8; j++)
            {
                if (!EVOLUTION_IS_STATE((bit >> j), 0x01))
                {
                    return  j + (g * 8);
                }
            }
        }
    }
    return 32;
}


u32 EisableBitNumber(u32 flag){
    for (s32 g = 0; g < 4; g++)
    {
        u8 bit = (u8)((flag >> (8 * g)) & 0xFF);
        if (EVOLUTION::FUNCTION::BitCount8(bit) != 0)
        {
            for (s32 j = 0; j < 8; j++)
            {
                if (EVOLUTION_IS_STATE((bit >> j), 0x01))
                {
                    return  j + (g * 8);
                }
            }
        }
    }
    return 32;
}

//�^�X�N�̎��s
void ThreadPool::Execute(u32 sleep_ms_time){

    //�^�X�N�̎��s
    u32 task_count = this->m_resistor_task_count;
    u32 f = 0;
    while (task_count != 0 && f < this->m_flag_cout)
    {
        u32& thread_group = this->mp_thread_use_flag[f];
        //group�̃r�b�g���O�a��Ԃ����ׂ�
        if (EVOLUTION::FUNCTION::BitCount32(thread_group) != 32)
        {
            s32 bit_number = DisableBitNumber(thread_group);
            u32 index = bit_number + (f * 32);
            //�X���b�h�v�[���I�[�o�[�`�F�b�N
            if (this->m_pool_count <= index)
            {
                break;
            }
            WorkThread* workthread = &this->mp_work_thread[index];
            TaskInfo* info = this->PopTask();
            workthread->mp_task = info->task;
            workthread->mp_parameter = info->parameter;
            //�T�X�y���h������
            ::ResumeThread(workthread->mp_thread->GetHandle());
            EVOLUTION_ENABLE_STATE(thread_group, (0x01 << bit_number));
            --task_count;
            continue;
        }
        ++f;
    }

    f = 0;
    while (f < this->m_flag_cout)
    {
        u32& thread_group = this->mp_thread_use_flag[f];
        //group�̃r�b�g���O�a��Ԃ����ׂ�
        if (EVOLUTION::FUNCTION::BitCount32(thread_group) != 0)
        {
            s32 bit_number = EisableBitNumber(thread_group);
            u32 index = bit_number + (f * 32);
            //�X���b�h�v�[���I�[�o�[�`�F�b�N
            if (this->m_pool_count <= index)
            {
                break;
            }
            WorkThread* workthread = &this->mp_work_thread[index];
            //�t���O�̃R�s�[
            workthread->m_pool_write_thread_read_flg = workthread->m_pool_read_thread_write_flg;
            if (EVOLUTION_IS_STATE(workthread->m_pool_write_thread_read_flg, THREAD_POOL_FLAG::END))
            {
                workthread->mp_task->OnEndExecute(workthread->mp_result);
                EVOLUTION_RELEASE(workthread->mp_result);
                EVOLUTION_RELEASE(workthread->mp_parameter);
                EVOLUTION_DISABLED_STATE(thread_group, (0x01 << bit_number));
                if (EVOLUTION_IS_STATE(workthread->m_pool_write_thread_read_flg, THREAD_POOL_FLAG::WAIT))
                {
                    EVOLUTION_DISABLED_STATE(workthread->m_pool_read_thread_write_flg, THREAD_POOL_FLAG::END);
                }
                EVOLUTION_DISABLED_STATE(workthread->m_pool_write_thread_read_flg, THREAD_POOL_FLAG::END);
            }
            continue;
        }
        ++f;
    }

    //�o�^����Ă���^�X�N���Ȃ����10�~���b�X���[�v
    if (this->m_resistor_task_count == 0)
    {
        Sleep(sleep_ms_time);
    }
}


//�^�X�N�̓o�^
ThreadResult::_RESULT ThreadPool::TaskExecute(ITask* task, IParameter* parameter){
    this->PushTask(task, parameter);
    return ThreadResult::RESULT_OK;
}

//���s�^�X�N�����擾
s32 ThreadPool::TaskExecuteCount()const{
    return  this->m_resistor_task_count;
}

//�^�X�N�̃L���[�ɐς�
void ThreadPool::PushTask(ITask* task, IParameter* parameter){
    HANDLE handle  = this->mp_mutex->Lock();
    parameter->AddRef();
    this->mp_taskinfo_queue_last->task = task;
    this->mp_taskinfo_queue_last->parameter = parameter;
    this->mp_taskinfo_queue_last++;
    u32 count = this->mp_taskinfo_queue_last - this->mp_taskinfo_queue_root;
    //���X�g�܂ōs���Ă����ꍇ�ŏ��ɖ߂�
    if (this->m_max_task_queue_count <= count)
    {
        this->mp_taskinfo_queue_last = this->mp_taskinfo_queue_root;
    }

    this->m_resistor_task_count++;
    this->mp_mutex->UnLock(handle);
    //�L���[�I�[�o�[
    if (this->mp_taskinfo_queue_last == this->mp_taskinfo_queue_first)
    {
        throw THREAD::ThreadException::CREATE_THREAD_POOL_EXCEPTION;
    }
}

//�^�X�N�̎擾
TaskInfo* ThreadPool::PopTask(){
    if (this->m_resistor_task_count == 0)
    {
        return nullptr;
    }
    HANDLE handle = this->mp_mutex->Lock();
    TaskInfo* info = this->mp_taskinfo_queue_first;
    this->mp_taskinfo_queue_first++;
    u32 count = this->mp_taskinfo_queue_first - this->mp_taskinfo_queue_root;
    //���X�g�܂ōs���Ă����ꍇ�ŏ��ɖ߂�
    if (this->m_max_task_queue_count <= count)
    {
        this->mp_taskinfo_queue_first = this->mp_taskinfo_queue_root;
    }
    this->m_resistor_task_count--;
    this->mp_mutex->UnLock(handle);
    return info;
}

void ThreadPool::Thread(ptr_t argument, const IThread* thread){
    WorkThread* work = (WorkThread*)argument;


    while (EVOLUTION_IS_STATE(work->m_pool_write_thread_read_flg, THREAD_POOL_FLAG::LOOP))
    {
        //�t���O�̃R�s�[
        work->m_pool_read_thread_write_flg = work->m_pool_write_thread_read_flg;
        EVOLUTION_DISABLED_STATE(work->m_pool_read_thread_write_flg, THREAD_POOL_FLAG::WAIT);
        if (work->mp_task != nullptr)
        {
            IResult* result;
            EVOLUTION::FUNCTION::CreateResult(&result);
            work->mp_task->Execute(work->mp_parameter, result);
            result->AddRef();
            work->mp_result = result;
            EVOLUTION_RELEASE(result);
            EVOLUTION_ENABLE_STATE(work->m_pool_read_thread_write_flg, THREAD_POOL_FLAG::END);
        }

        EVOLUTION_ENABLE_STATE(work->m_pool_read_thread_write_flg, THREAD_POOL_FLAG::WAIT);
        SuspendThread(work->mp_thread->GetHandle());
    }

}


//-----------------------------------------------
//���[�J�[�X���b�h
//-----------------------------------------------
WorkThread::WorkThread() :
m_pool_write_thread_read_flg(0),
m_pool_read_thread_write_flg(0),
mp_result(nullptr),
mp_parameter(nullptr),
mp_task(nullptr),
mp_mutex(nullptr),
mp_thread(nullptr)
{

}

RESULT WorkThread::Initialise(u32 stack_size){
    EVOLUTION::FUNCTION::CreateThread((IThread**)&this->mp_thread, stack_size);
    EVOLUTION::FUNCTION::CreateThreadMutex(&this->mp_mutex);
    return  _RESULT::S_ok;
}