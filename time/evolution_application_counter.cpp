#include "evolution_timer_implement.h"
#include <sys/time.h>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::TIMER;

//IUnknown

u32 HighQualityApplicationCounter::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT HighQualityApplicationCounter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IApplicationCounter)) {
        *ppvObject = static_cast<IApplicationCounter*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_HighQualityApplicationCounter)) {
        *ppvObject = static_cast<HighQualityApplicationCounter*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 HighQualityApplicationCounter::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

HighQualityApplicationCounter::HighQualityApplicationCounter() {

}

HighQualityApplicationCounter::~HighQualityApplicationCounter() {

}

RESULT HighQualityApplicationCounter::Create() {
    gettimeofday(&m_start, NULL);
    return _RESULT::S_ok;
}

//アプリケーションが開始してからの経過時間

u64 HighQualityApplicationCounter::GetMilliSecondU64()const {
    struct timeval now;
    gettimeofday(&now, NULL);
    u64 sec = (now.tv_sec - this->m_start.tv_sec)* 1000000LL;
    u64 ms = (now.tv_usec - this->m_start.tv_usec) * 1000LL;
    return sec + ms;
}

//アプリケーションが開始してからの経過時間

u32 HighQualityApplicationCounter::GetMilliSecondU32()const {
    struct timeval now;
    gettimeofday(&now, NULL);
    u64 sec = (now.tv_sec - this->m_start.tv_sec)* 1000000LL;
    u64 ms = (now.tv_usec - this->m_start.tv_usec) * 1000LL;
    return (u32) (sec + ms);
}

//------------------------------------------------------------------------------
//
//              ApplicationCounter
//
//------------------------------------------------------------------------------
//IUnknown

u32 ApplicationCounter::AddRef() {
    return m_instance_counter.AddRef();
}

RESULT ApplicationCounter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject) {
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown)) {
        *ppvObject = static_cast<IUnknown*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IApplicationCounter)) {
        *ppvObject = static_cast<IApplicationCounter*> (this);
        this->AddRef();
    } else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ApplicationCounter)) {
        *ppvObject = static_cast<ApplicationCounter*> (this);
        this->AddRef();
    } else {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 ApplicationCounter::Release() {
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0) {
        delete this;
    }
    return counter;
}

ApplicationCounter::ApplicationCounter() {

}

ApplicationCounter::~ApplicationCounter() {
}

RESULT ApplicationCounter::Create() {
    gettimeofday(&this->m_start, NULL);
    return _RESULT::S_ok;
}

//アプリケーションが開始してからの経過時間

u64 ApplicationCounter::GetMilliSecondU64()const {
    struct timeval now;
    gettimeofday(&now, NULL);
    u64 sec = (now.tv_sec - this->m_start.tv_sec)* 1000000LL;
    u64 ms = (now.tv_usec - this->m_start.tv_usec) * 1000LL;
    return (u32) (sec + ms);
}

//アプリケーションが開始してからの経過時間

u32 ApplicationCounter::GetMilliSecondU32()const {
    struct timeval now;
    gettimeofday(&now, NULL);
    u64 sec = (now.tv_sec - this->m_start.tv_sec)* 1000000LL;
    u64 ms = (now.tv_usec - this->m_start.tv_usec) * 1000LL;
    return (u32) (sec + ms);
}

