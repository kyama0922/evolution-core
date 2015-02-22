#include "evolution_thread_implement.h"
#include "../function/evolution_function.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;


u16 Mutex::unique_id = 0x0001;
u64 Mutex::CreateUniqueId(){
    u64 buf = 0;
    EVOLUTION::FUNCTION::Base64encode((u8*)&unique_id, sizeof(Mutex::unique_id), (u8*)&buf);
    unique_id++;
    return buf;
}

//IUnknown
u32 Mutex::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Mutex::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IMutex))
    {
        *ppvObject = static_cast<IMutex*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_Mutex))
    {
        *ppvObject = static_cast<Mutex*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 Mutex::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}


Mutex::Mutex() : m_mutex_handle(NULL){
    u64 id = Mutex::CreateUniqueId();
    memcpy(m_id, &id, sizeof(u64));
    this->m_mutex_handle = CreateMutex(NULL, FALSE, (LPCWSTR)&this->m_id);
}

Mutex::~Mutex(){
    CloseHandle(this->m_mutex_handle);
}

HANDLE Mutex::Lock()const{
    return OpenMutex(MUTEX_ALL_ACCESS, FALSE, (LPCWSTR)m_id);
}

ThreadResult::_RESULT Mutex::UnLock(HANDLE lock_handle)const{
    if (ReleaseMutex(lock_handle))
    {
        return ThreadResult::RESULT_OK;
    }
    return ThreadResult::MUTEX_RELEASE_FAILED;
}
