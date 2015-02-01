#include "evolution_thread_implement.h"
#include "../etc/evolution_assert.h"


using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::THREAD;


//IUnknown
u32 Parameter::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT Parameter::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IParameter))
    {
        *ppvObject = static_cast<IParameter*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_Parameter))
    {
        *ppvObject = static_cast<Parameter*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return _RESULT::E_no_instance;
    }

    return _RESULT::S_ok;
}

u32 Parameter::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}


Parameter::Parameter() : m_parameter_count(0), mp_parameter(nullptr)
{

}

Parameter::~Parameter(){
    for (size_t i = 0; i < this->m_parameter_count; i++)
    {
        u8* ptr = (u8*)this->mp_parameter[i].pointer;
        this->mp_parameter[i].pointer = 0;
        EVOLUTION_DELETE(ptr);
    }
    EVOLUTION_DELETE_ARRAY(this->mp_parameter);
}

//作成したパラメーター数を取得します。
u32 Parameter::GetParameterCount()const{
    return this->m_parameter_count;
}

//パラメーターを作成します。
ThreadResult::_RESULT Parameter::CreateParameters(u32 param_count) {
    m_parameter_count = param_count;
    this->mp_parameter = NEW Parameter::_Parameter[this->m_parameter_count];
    for (u32 i = 0; i < this->m_parameter_count; i++)
    {
        this->mp_parameter[i].pointer = 0;
        this->mp_parameter[i].size = 0;
    }
    return ThreadResult::RESULT_OK;
}

//パラメーター用メモリを確保します。
ThreadResult::_RESULT Parameter::CreateParameterMemory(u32 index, u32 param_size){
    if (this->m_parameter_count < index){
       return ThreadResult::PARAMETER_INDEX_OVER_FAILED;
    }
    void* ptr = (void*)this->mp_parameter[index].pointer;
    this->mp_parameter[index].pointer = 0;
    EVOLUTION_DELETE(ptr);

    this->mp_parameter[index].pointer = (ptr_t)NEW u8[param_size];
    this->mp_parameter[index].size = param_size;

    return ThreadResult::RESULT_OK;
}
//パラメーターサイズを取得します。
u32 Parameter::GetParameterSize(u32 index)const{
    return this->mp_parameter[index].size;
}

//パラメーターに値をセットします。
ThreadResult::_RESULT Parameter::SetParameter(u32 index,const void* val, u32 param_size){
    if (this->m_parameter_count < index){
        return ThreadResult::PARAMETER_INDEX_OVER_FAILED;
    }

    if (this->mp_parameter[index].size < param_size){
        return ThreadResult::SET_SIZE_OVER_FAILED;
    }
    u8* dest_ptr = (u8*)this->mp_parameter[index].pointer;
    u8* src_ptr = (u8*)val;

    for (u32 i = 0; i < param_size; i++, dest_ptr++, src_ptr++)
    {
        *dest_ptr = *src_ptr;
    }
    return ThreadResult::RESULT_OK;
}

//パラメーターを取得します。
const void* Parameter::GetParameter(u32 index)const{
    if (this->m_parameter_count < index){
        return nullptr;
    }
    return (void*)this->mp_parameter[index].pointer;
}