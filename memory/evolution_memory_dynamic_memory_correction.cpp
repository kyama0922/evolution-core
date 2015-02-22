#include "evolution_memory_dynamic_memory_correction.h"


using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::MEMORY;

//---------------------------------------------------------
//  MemoryNode
//---------------------------------------------------------
//IUnknown
u32 MemoryNode::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT MemoryNode::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    //else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IStaticMemoryManager))
    //{
    //    *ppvObject = static_cast<IStaticMemoryManager*>(this);
    //    this->AddRef();
    //}
    //else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_TLSFMemoryAllocator))
    //{
    //    *ppvObject = static_cast<TLSFMemoryAllocator*>(this);
    //    this->AddRef();
    //}
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 MemoryNode::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

RESULT MemoryNode::GetMemoryManager(IDynamicMemoryManager** memory_manager)const{
    return RESULT::E_unknown;
}

ptr_size_t MemoryNode::GetSize()const{
    return 0;
}

RESULT  MemoryNode::Lock(ptr_t* ref_data_ptr)const{
    return RESULT::E_unknown;
}

RESULT  MemoryNode::Lock(void** ref_data_ptr)const{
    return RESULT::E_unknown;
}

RESULT MemoryNode::UnLock()const{
    return RESULT::E_unknown;
}


//---------------------------------------------------------
//  DynamicMemoryManager
//---------------------------------------------------------

//IUnknown
u32 DynamicMemoryManager::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT DynamicMemoryManager::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    return RESULT::E_unknown;
}

u32 DynamicMemoryManager::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        delete this;
    }
    return counter;
}

DynamicMemoryManager::DynamicMemoryManager(ptr_size_t size) :  m_size(size) {
    mp_pointer = (ptr_t)malloc(m_size);
}

DynamicMemoryManager::DynamicMemoryManager(ptr_t pointer, ptr_size_t size) : mp_pointer(pointer), m_size(size) {

}

DynamicMemoryManager::~DynamicMemoryManager(){

}

//作成したNodeの数
ptr_size_t DynamicMemoryManager::GetNodeNum(){
    return 0;
}

//ノードの作成
RESULT DynamicMemoryManager::CreateMemoryNode(IMemoryNode** memory_node, ptr_size_t size){
    return RESULT::E_unknown;
}

//ノードをCompactionする
RESULT DynamicMemoryManager::Compaction(){
    return RESULT::E_unknown;
}
//管理してるMemoryサイズ
ptr_size_t DynamicMemoryManager::GetHeapSize(){
    return this->m_size;
}
//使用中のMemoryサイズ
ptr_size_t DynamicMemoryManager::GetUseHeapSize(){
    return RESULT::E_unknown;
}


//ノードコンパクションロック
RESULT DynamicMemoryManager::LockNodeResistor(IMemoryNode* node){
    return RESULT::E_unknown;
}

//ノードコンパクションアンロック
RESULT DynamicMemoryManager::UnLockNodeResistor(IMemoryNode* node){
    return RESULT::E_unknown;
}