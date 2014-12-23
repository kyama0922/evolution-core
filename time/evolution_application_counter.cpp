#include "evolution_timer_implement.h"
#include <Windows.h>
#pragma comment(lib,"Kernel32.lib")

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::TIMER;

//IUnknown
u32 ApplicationCounter::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT ApplicationCounter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IApplicationCounter))
    {
        *ppvObject = static_cast<IApplicationCounter*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_ApplicationCounter))
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

}

RESULT ApplicationCounter::Create(){
    //�N���b�N�����擾
    if (QueryPerformanceFrequency(&this->m_clock))
    {   
        //�A�v���P�[�V�����N�����Ԃ𑪒�
        QueryPerformanceCounter(&this->m_start);
    }

    return _RESULT::S_ok;
}

//�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
u64 ApplicationCounter::GetMilliSecondU64()const{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return  ((now.QuadPart - this->m_start.QuadPart) * 1000LL) / this->m_clock.QuadPart;
}

//�A�v���P�[�V�������J�n���Ă���̌o�ߎ���
u32 ApplicationCounter::GetMilliSecondU32()const{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return  (u32)(((now.QuadPart - this->m_start.QuadPart) * 1000LL) / this->m_clock.QuadPart);
}