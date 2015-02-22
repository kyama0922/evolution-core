#include "../etc/evolution_assert.h"
#include "evolution_stack_memory_manager.h"
#include <new>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::MEMORY;

//メモリマネージャー外の確保したメモリを渡す
RESULT EVOLUTION::FUNCTION::CreateStackMemoryManager(CORE::MEMORY::IStackMemoryManager** memory_manager, ptr_size_t size){
    void* p = malloc(sizeof(StackMemoryManager));
    if (p == nullptr)
    {
        return _RESULT::E_unknown;
    }
    StackMemoryManager* stack_memory_manager = new(p)StackMemoryManager();
    if (stack_memory_manager == nullptr)
    {
        return _RESULT::E_unknown;
    }
    *memory_manager = stack_memory_manager;
    stack_memory_manager->CreateMemory(size);
    return _RESULT::S_ok;
}

//メモリマネージャー外の確保したメモリを渡す
RESULT EVOLUTION::FUNCTION::CreateStackMemoryManager(CORE::MEMORY::IStackMemoryManager** memory_manager, ptr_t pointer, ptr_size_t size){
    StackMemoryManager* stack_memory_manager = new((void*)pointer)StackMemoryManager();
    if (stack_memory_manager == nullptr)
    {
        return _RESULT::E_unknown;
    }
    *memory_manager = stack_memory_manager;
    stack_memory_manager->CreateMemory(pointer + sizeof(StackMemoryManager), size - sizeof(StackMemoryManager));
    return _RESULT::S_ok;
}



//IUnknown
u32 StackMemoryManager::AddRef(){
    return m_instance_counter.AddRef();
}

RESULT StackMemoryManager::QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject){
    if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_IStackMemoryManager)){
        *ppvObject = static_cast<IStackMemoryManager*>(this);
        this->AddRef();
    }
    else if (EVOLUTION_EQUALGUID(riid, EVOLUTION_GUID::IID_StackMemoryManager)){
        *ppvObject = static_cast<StackMemoryManager*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }

    return RESULT::S_ok;
}

u32 StackMemoryManager::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        if (EVOLUTION_IS_STATE(this->m_flag, StackMemoryManager::FLAG::MEMORY_DELETE))
        {
            this->~StackMemoryManager();
            free(this);
        }
        else
        {
            this->~StackMemoryManager();
        }
    }
    return counter;
}



StackMemoryManager::StackMemoryManager() :m_pointer(0), m_use_pointer(0), m_memory_size(0), m_flag(0){

}

StackMemoryManager::~StackMemoryManager(){
    if (EVOLUTION_IS_STATE(this->m_flag, StackMemoryManager::FLAG::MEMORY_DELETE))
    {
        void* ptr = (void*)this->m_pointer;
        EVOLUTION_DELETE_ARRAY(ptr);

    }
    this->m_flag = 0;
    this->m_pointer = 0;
    this->m_use_pointer = 0;
    this->m_memory_size = 0;
}

RESULT StackMemoryManager::CreateMemory(ptr_size_t memory_size){
    this->m_memory_size = memory_size;
    this->m_use_pointer = this->m_pointer = (ptr_t)NEW u8[this->m_memory_size];
    EVOLUTION_ENABLE_STATE(this->m_flag, StackMemoryManager::FLAG::MEMORY_DELETE);

    return RESULT::S_ok;
}

RESULT StackMemoryManager::CreateMemory(ptr_t pointer, ptr_size_t memory_size){
    this->m_memory_size = memory_size;
    this->m_use_pointer = this->m_pointer = pointer;
    EVOLUTION_DISABLED_STATE(this->m_flag, StackMemoryManager::FLAG::MEMORY_DELETE);
    return RESULT::S_ok;
}

void* StackMemoryManager::Push(ptr_size_t size, ptr_size_t alignment){
    void* pointer = 0;
    ptr_size_t offset = sizeof(StackMemoryManager::BLOCK_HEADER);

    ptr_t ptr = (this->m_use_pointer + offset);
    if ((ptr & (alignment - 1)) != 0){
        offset += alignment - (ptr & (alignment - 1));
    }
    StackMemoryManager::BLOCK_HEADER* header = (StackMemoryManager::BLOCK_HEADER*)(this->m_use_pointer + offset - sizeof(StackMemoryManager::BLOCK_HEADER));
    header->endcode = (ptr_size_t)0xCDCDCDCDCDCDCDCD;
    header->offset = offset - sizeof(StackMemoryManager::BLOCK_HEADER);
    header->ptr_size = size;
    //ヘッダーサイズ分すすめる
    this->m_use_pointer += offset;

    pointer = (void*)this->m_use_pointer;

    //使用数分すすめる
    this->m_use_pointer += size;
    return pointer;
}

void StackMemoryManager::Pop(void* pointer){
    ptr_t ptr = (ptr_t)pointer;

    StackMemoryManager::BLOCK_HEADER* header = (StackMemoryManager::BLOCK_HEADER*)(ptr - sizeof(StackMemoryManager::BLOCK_HEADER));

    EVOLUTION_ASSERT(header->endcode == (ptr_size_t)0xCDCDCDCDCDCDCDCD);

    this->m_use_pointer = ptr - sizeof(StackMemoryManager::BLOCK_HEADER) - header->offset;

}

void StackMemoryManager::PopAll(){
    this->m_use_pointer = this->m_pointer;
}