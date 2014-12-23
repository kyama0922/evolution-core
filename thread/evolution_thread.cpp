#include "evolution_thread_implement.h"
#include "../etc/evolution_assert.h"

#include <process.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;

#define MUTEX_NAME "EVOLUTION::CORE::THREAD::Thread_Mutex"

//IUnknown
u32 Thread::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Thread::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IThread))
    {
        *ppvObject = static_cast<IThread*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Thread))
    {
        *ppvObject = static_cast<Thread*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 Thread::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

Thread::Thread(u32 stack_size) :m_stack_size(stack_size), m_thread_handle(NULL), m_lock_handle(NULL), mp_mutex(nullptr) , m_function_pointer(nullptr) , m_argument(0){

}
Thread::~Thread(){
    if (this->m_thread_handle){
        CloseHandle(this->m_thread_handle);
        this->m_thread_handle = NULL;
    }
    EVOLUTION_RELEASE(this->mp_mutex);
}

ThreadResult::_RESULT Thread::Run(void(*function)(ptr_t argument, const IThread* thread), ptr_t argument){
    if (this->m_thread_handle != NULL){
        return ThreadResult::RUNNING_FAILED;
    }
    this->AddRef();
    this->m_function_pointer = function;
    this->m_argument = argument;
    this->m_thread_handle = (HANDLE)_beginthreadex(nullptr, this->m_stack_size, Thread::Start, this, 0, nullptr);
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Join(){
    u32 ret = WaitForSingleObject(this->m_thread_handle, INFINITE);
    if (WAIT_TIMEOUT == ret)
    {
        return ThreadResult::WAIT_TIME_OUT_FAILED;
    }
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Join(u32 time_out){
    u32 ret = WaitForSingleObject(this->m_thread_handle, INFINITE);
    if (WAIT_TIMEOUT == ret)
    {
        return ThreadResult::WAIT_TIME_OUT_FAILED;
    }
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Lock(IMutex* mutex)const{
    mutex->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_Mutex, (void**)&this->mp_mutex);
    //明示的に変更
    const_cast<HANDLE>(this->m_lock_handle) = this->mp_mutex->Lock();

    if (this->m_lock_handle == NULL)
    {
        return ThreadResult::LOCK_FAILED;
    }
    else if (WaitForSingleObject(this->m_lock_handle, INFINITE) != WAIT_ABANDONED)
    {
        return  ThreadResult::LOCK_FAILED;
    }

    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::UnLock()const{
    if (this->mp_mutex->UnLock(this->m_lock_handle))
    {
        //明示的に変更
        const_cast<HANDLE>(this->m_lock_handle) = NULL;
        return ThreadResult::MUTEX_RELEASE_FAILED;
    }
    EVOLUTION_RELEASE(const_cast<Mutex*>(this->mp_mutex));
    return ThreadResult::RESULT_OK;
}

bool Thread::IsRun()const{
    return (this->m_thread_handle == NULL) ? false : true;
}

bool Thread::IsEnd()const{
    if (this->m_thread_handle == NULL){
        return false;
    }
    DWORD exitcode;
    GetExitCodeThread(this->m_thread_handle, &exitcode);
    return STILL_ACTIVE != exitcode;
}

HANDLE Thread::GetHandle()const{
    return this->m_thread_handle;
}

unsigned _stdcall Thread::Start(void* myself){
    Thread* This = (Thread*)myself;
    try{
#define this This
        this->m_function_pointer(this->m_argument, this);

    }
    catch (...)
    {
        EVOLUTION_ASSERT_MESSAGE(false, "Thread Hang-Up");
    }
    This->Release();
    if (this->m_thread_handle){
        CloseHandle(this->m_thread_handle);
        this->m_thread_handle = NULL;
    }
    _endthreadex(0x00);
    return 0;
#undef this
}