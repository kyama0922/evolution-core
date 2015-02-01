#include "evolution_thread_implement.h"
#include "../function/evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;


u16 Mutex::unique_id = 0x0001;

u64 Mutex::CreateUniqueId() {
    u64 buf = 0;
    EVOLUTION::FUNCTION::Base64encode((u8*) & unique_id, sizeof (Mutex::unique_id), (u8*) & buf);
    unique_id++;
    return buf;
}

//IUnknown

u32 Mutex::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT Mutex::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IMutex)) {
        *ppvObject = static_cast<IMutex*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Mutex)) {
        *ppvObject = static_cast<Mutex*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 Mutex::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

Mutex::Mutex() {
    u64 id = Mutex::CreateUniqueId();
    pthread_mutexattr_init(&this->m_mutex_attr);
    pthread_mutex_init(&this->m_mutex_handle, &m_mutex_attr);

}

Mutex::~Mutex() {
    pthread_mutexattr_destroy(&this->m_mutex_attr);
    pthread_mutex_destroy(&this->m_mutex_handle);
}

s32 Mutex::Lock() {
    return pthread_mutex_trylock(&this->m_mutex_handle);
}

ThreadResult::_RESULT Mutex::UnLock() {
    if (pthread_mutex_unlock(&this->m_mutex_handle) == 0) {
        return ThreadResult::RESULT_OK;
    }
    return ThreadResult::MUTEX_RELEASE_FAILED;
}

pthread_mutex_t* Mutex::GetMutex(){
    return &this->m_mutex_handle;
}
