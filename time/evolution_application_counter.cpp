#include "evolution_timer_implement.h"
#include <Windows.h>
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib, "winmm.lib")

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::TIMER;

//IUnknown
u32 HighQualityApplicationCounter::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT HighQualityApplicationCounter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IApplicationCounter))
    {
        *ppvObject = static_cast<IApplicationCounter*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_HighQualityApplicationCounter))
    {
        *ppvObject = static_cast<HighQualityApplicationCounter*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 HighQualityApplicationCounter::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

HighQualityApplicationCounter::HighQualityApplicationCounter(){

}
HighQualityApplicationCounter::~HighQualityApplicationCounter(){

}

RESULT HighQualityApplicationCounter::Create(){
    //クロック数を取得
    if (QueryPerformanceFrequency(&this->m_clock))
    {
        //アプリケーション起動時間を測定
        QueryPerformanceCounter(&this->m_start);
    }

    return _RESULT::S_ok;
}

//アプリケーションが開始してからの経過時間
u64 HighQualityApplicationCounter::GetMilliSecondU64()const{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return  ((now.QuadPart - this->m_start.QuadPart) * 1000LL) / this->m_clock.QuadPart;
}

//アプリケーションが開始してからの経過時間
u32 HighQualityApplicationCounter::GetMilliSecondU32()const{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return  (u32)(((now.QuadPart - this->m_start.QuadPart) * 1000LL) / this->m_clock.QuadPart);
}

//------------------------------------------------------------------------------
//
//              ApplicationCounter
//
//------------------------------------------------------------------------------
//IUnknown
u32 ApplicationCounter::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT ApplicationCounter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IApplicationCounter))
    {
        *ppvObject = static_cast<IApplicationCounter*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_ApplicationCounter))
    {
        *ppvObject = static_cast<ApplicationCounter*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 ApplicationCounter::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

ApplicationCounter::ApplicationCounter(){

}
ApplicationCounter::~ApplicationCounter(){
    timeEndPeriod(1);
}

RESULT ApplicationCounter::Create(){
    timeBeginPeriod(1);
    //アプリケーション起動時間を測定
    this->m_start = timeGetTime();

    return _RESULT::S_ok;
}

//アプリケーションが開始してからの経過時間
u64 ApplicationCounter::GetMilliSecondU64()const{
    u32 now = timeGetTime();
    return (u64)(now - this->m_start);
}

//アプリケーションが開始してからの経過時間
u32 ApplicationCounter::GetMilliSecondU32()const{
    u32 now = timeGetTime();
    return (u64)(now - this->m_start);
}

