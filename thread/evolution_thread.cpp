#include "evolution_thread_implement.h"
#include "../etc/evolution_assert.h"
#include <errno.h>
using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;

#define MUTEX_NAME "EVOLUTION::CORE::THREAD::Thread_Mutex"

//IUnknown

u32 Thread::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT Thread::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IThread)) {
        *ppvObject = static_cast<IThread*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Thread)) {
        *ppvObject = static_cast<Thread*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 Thread::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

Thread::Thread(u32 stack_size) : m_stack_size(stack_size), m_thread_handle(NULL), mp_mutex(nullptr), m_function_pointer(nullptr), m_argument(0) {
    pthread_attr_init(&this->m_thread_attr);
    pthread_attr_setguardsize(&this->m_thread_attr, this->m_stack_size);
}

Thread::~Thread() {
    if (this->m_thread_handle) {
        pthread_join(this->m_thread_handle, NULL);
        this->m_thread_handle = NULL;
    }
    pthread_attr_destroy(&this->m_thread_attr);
    EVOLUTION_RELEASE(this->mp_mutex);
}

ThreadResult::_RESULT Thread::Run(void(*function)(ptr_t argument, const IThread* thread), ptr_t argument) {
    if (EVOLUTION_IS_STATE(this->m_state, THREAD_STATE_FLAG::RUN)) {
        return ThreadResult::RUNNING_FAILED;
    }
    this->AddRef();
    this->m_function_pointer = function;
    this->m_argument = argument;
    EVOLUTION_ENABLE_STATE(m_state, THREAD_STATE_FLAG::RUN);
    pthread_create(&this->m_thread_handle, &this->m_thread_attr, Thread::Start, this);
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Join() {
    if (this->m_thread_handle) {
        u32 ret = pthread_join(this->m_thread_handle, NULL);
        //    if (WAIT_TIMEOUT == ret) {
        //        return ThreadResult::WAIT_TIME_OUT_FAILED;
        //    }
    }
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Join(u32 time_out_ms) {
    if (this->m_thread_handle) {
        timespec time;
        clock_gettime(CLOCK_REALTIME, &time);
        time.tv_nsec += time_out_ms * 1000000LL;
        u32 ret = pthread_timedjoin_np(this->m_thread_handle, NULL, &time);

        if (ETIMEDOUT == ret) {
            return ThreadResult::WAIT_TIME_OUT_FAILED;
        }
    }
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::Lock(IMutex* mutex)const {
    mutex->QueryInterface(EVOLUTION::EVOLUTION_GUID::IID_Mutex, (void**) & this->mp_mutex);

    if (this->mp_mutex->Lock()) {
        return ThreadResult::LOCK_FAILED;
    }
    return ThreadResult::RESULT_OK;
}

ThreadResult::_RESULT Thread::UnLock()const {
    if (EVOLUTION_FAILED(this->mp_mutex->UnLock())) {
        return ThreadResult::MUTEX_RELEASE_FAILED;
    }
    Mutex** m = (Mutex**) & this->mp_mutex;
    (*m)->Release();
    *m = nullptr;
    return ThreadResult::RESULT_OK;
}

bool Thread::IsRun()const {
    return EVOLUTION_IS_STATE(this->m_state, THREAD_STATE_FLAG::RUN);
}

bool Thread::IsEnd()const {
    return !EVOLUTION_IS_STATE(m_state, THREAD_STATE_FLAG::RUN);
}

pthread_t Thread::GetHandle()const {
    return this->m_thread_handle;
}

void* Thread::Start(void* myself) {
    Thread* This = (Thread*) myself;
#define this This
    this->m_function_pointer(this->m_argument, this);

    if (this->m_thread_handle) {
        pthread_detach(this->m_thread_handle);
        this->m_thread_handle = NULL;
    }
    EVOLUTION_DISABLED_STATE(this->m_state, THREAD_STATE_FLAG::RUN);
    This->Release();
    return 0;
#undef this
}