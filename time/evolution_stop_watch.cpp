#include "evolution_timer_implement.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::TIMER;

//IUnknown
u32 StopWatch::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT StopWatch::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IStopWatch))
    {
        *ppvObject = static_cast<IStopWatch*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_StopWatch))
    {
        *ppvObject = static_cast<StopWatch*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 StopWatch::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

StopWatch::StopWatch() : m_start(false) ,m_start_time(0) , m_stop_time(0){

}

StopWatch::~StopWatch(){
    EVOLUTION_RELEASE(this->mp_application_counter);
}

RESULT StopWatch::Create(){
    EVOLUTION::FUNCTION::CreateApplicationCounter(&this->mp_application_counter);
    return _RESULT::S_ok;
}

//“®‚©‚·
void StopWatch::Start(){
    this->m_start = true;
    this->m_start_time = this->mp_application_counter->GetMilliSecondU32();
}
//’âŽ~
void StopWatch::Stop(){
    this->m_start = false;
    this->m_start_time = this->m_stop_time = this->mp_application_counter->GetMilliSecondU32();
}
//ˆêŽž’âŽ~
void StopWatch::Pause(){
    this->m_start = false;
    this->m_stop_time = this->mp_application_counter->GetMilliSecondU32();
}
//ÄŠJ
void StopWatch::RePause(){
    this->m_start = true;
    this->m_start_time = this->mp_application_counter->GetMilliSecondU32() - this->m_stop_time;
}

//“®‚©‚µ‚Ä‚¢‚é
bool StopWatch::IsStart()const{
    return this->m_start;
}
//Œ»ÝŽžŠÔ‚ÌŽæ“¾(millisecond)
u32 StopWatch::GetMilliSecondU32()const{
    if (this->m_start){
        return (u32)this->mp_application_counter->GetMilliSecondU32() - this->m_start_time;
    }
    return this->m_stop_time - this->m_start_time;
}

//Œ»ÝŽžŠÔ‚ÌŽæ“¾(second)
u32 StopWatch::GetSecondU32()const{
    if (this->m_start){
        return ((u32)this->mp_application_counter->GetMilliSecondU32() - this->m_start_time) / 1000;
    }
    return (this->m_stop_time - this->m_start_time) / 1000;
}