#include "evolution_thread_implement.h"
#include "../etc/evolution_assert.h"

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;


//IUnknown
u32 Result::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Result::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IResult))
    {
        *ppvObject = static_cast<IResult*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Result))
    {
        *ppvObject = static_cast<Result*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 Result::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}




Result::Result() : m_value_pointer(0), m_value_size(0){

}
Result::~Result(){
    u8* ptr = (u8*)this->m_value_pointer;
    this->m_value_pointer = 0;
    EVOLUTION_DELETE(ptr);
}

ThreadResult::_RESULT Result::CreateResultMemory(u32 value_size){
    u8* ptr = (u8*)this->m_value_pointer;
    this->m_value_pointer = 0;
    EVOLUTION_DELETE(ptr);

    this->m_value_pointer = (ptr_t)NEW u8[value_size];
    if (this->m_value_pointer == 0)
    {
        return ThreadResult::SET_MEMORY_FAILED;
    }
    this->m_value_size = value_size;

    return ThreadResult::RESULT_OK;
}

//Resultの設定
ThreadResult::_RESULT Result::SetResult(const void* value, u32 value_size){
    if (value_size < this->m_value_size)
    {
        return  ThreadResult::SET_SIZE_OVER_FAILED;
    }

    u8* dest_ptr = (u8*)this->m_value_pointer;
    u8* src_ptr = (u8*)value;

    for (u32 i = 0; i < value_size; i++, dest_ptr++, src_ptr++)
    {
        *dest_ptr = *src_ptr;
    }
    return ThreadResult::RESULT_OK;
}
//Resultの値のサイズ
u32 Result::GetResultSize()const{
    return this->m_value_size;
}
//Resultの取得
void* Result::GetResult()const{
    return (void*)this->m_value_pointer;
}
