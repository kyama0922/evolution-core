#include "evolution_memory_tlsf_allocator.h"
#include <new>

using namespace EVOLUTION;
using namespace EVOLUTION::CORE;
using namespace EVOLUTION::CORE::MEMORY;


//�������}�l�[�W���[�̍쐬
RESULT EVOLUTION::FUNCTION::CreateTLSFStaticMemoryManager(CORE::MEMORY::IStaticMemoryManager** memory_manager, ptr_size_t size){
    void* p = malloc(sizeof(TLSFMemoryAllocator));
    if (p == nullptr)
    {
        throw MemoryException::CREATING_A_MEMORY_MANAGER_FAILURE;
    }
    TLSFMemoryAllocator* static_memory_manager = new(p)TLSFMemoryAllocator(size);
    if (static_memory_manager == nullptr)
    {
        throw MemoryException::CREATING_A_MEMORY_MANAGER_FAILURE;
    }
    *memory_manager = static_memory_manager;
    static_memory_manager->Initialize();
    return _RESULT::S_ok;
}

//�������}�l�[�W���[�̍쐬
RESULT EVOLUTION::FUNCTION::CreateTLSFStaticMemoryManager(CORE::MEMORY::IStaticMemoryManager** memory_manager, ptr_t pointer, ptr_size_t size){
    TLSFMemoryAllocator* static_memory_manager = new((void*)pointer)TLSFMemoryAllocator(pointer - sizeof(TLSFMemoryAllocator), size);
    if (static_memory_manager == nullptr)
    {
        throw MemoryException::CREATING_A_MEMORY_MANAGER_FAILURE;
    }
    *memory_manager = static_memory_manager;
    static_memory_manager->Initialize();
    return _RESULT::S_ok;
}

//IUnknown
u32 TLSFMemoryAllocator::AddRef(){
    return this->m_instance_counter.AddRef();
}

RESULT TLSFMemoryAllocator::QueryInterface(EVOLUTION_IID riid, void **ppvObject){
    if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IUnknown))
    {
        *ppvObject = static_cast<IUnknown *>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_IStaticMemoryManager))
    {
        *ppvObject = static_cast<IStaticMemoryManager*>(this);
        this->AddRef();
    }
    else if (IsEqualGUID(riid, EVOLUTION_GUID::IID_TLSFMemoryAllocator))
    {
        *ppvObject = static_cast<TLSFMemoryAllocator*>(this);
        this->AddRef();
    }
    else
    {
        *ppvObject = nullptr;
        return RESULT::E_no_instance;
    }
    return RESULT::S_ok;
}

u32 TLSFMemoryAllocator::Release(){
    u32 counter = this->m_instance_counter.Release();
    if (counter == 0){
        if (this->m_on_free)
        {
            this->~TLSFMemoryAllocator();
            free(this);
        }
        else
        {
            this->~TLSFMemoryAllocator();
        }
    }
    return counter;
}

TLSFMemoryAllocator::TLSFMemoryAllocator(ptr_size_t size) :m_use_memory_size(0), m_memory_size(size), m_on_free(true){
    this->mp_memory_pool = (ptr_t)malloc(size);
    this->m_tlsf_instance = tlsf_create_with_pool((void*)this->mp_memory_pool, m_memory_size);

}

TLSFMemoryAllocator::TLSFMemoryAllocator(ptr_t pointer, ptr_size_t size) : m_use_memory_size(0), mp_memory_pool(pointer), m_on_free(false){
    this->m_tlsf_instance = tlsf_create_with_pool((void*)this->mp_memory_pool, m_memory_size);
}

TLSFMemoryAllocator::~TLSFMemoryAllocator(){
    tlsf_destroy(this->m_tlsf_instance);
    if (m_on_free)
    {
        free((void*)this->mp_memory_pool);
    }
}

void TLSFMemoryAllocator::Initialize(){
    this->mp_debug_map = new std::map<ptr_t, Debug_Check_Header*>();
}
//�R���p�N�V��������Ȃ��������̊m��
void* TLSFMemoryAllocator::New(ptr_size_t size){
    void* pointer = tlsf_malloc(this->m_tlsf_instance, size);
    this->m_use_memory_size += tlsf_block_size(pointer);
    return pointer;
}

//�R���p�N�V��������Ȃ��z�񃁃����̊m��
void* TLSFMemoryAllocator::NewArray(ptr_size_t size){
    void* pointer = tlsf_malloc(this->m_tlsf_instance, size);
    this->m_use_memory_size += tlsf_block_size(pointer);
    return pointer;
}

//�R���p�N�V��������Ȃ��m�[�h�̍쐬
void TLSFMemoryAllocator::Delete(void* pointer){
    this->m_use_memory_size -= tlsf_block_size(pointer);
    tlsf_free(this->m_tlsf_instance, pointer);
}

//�R���p�N�V��������Ȃ��m�[�h�̍쐬
void TLSFMemoryAllocator::DeleteArray(void* pointer){
    this->m_use_memory_size -= tlsf_block_size(pointer);
    tlsf_free(this->m_tlsf_instance, pointer);
}

//�Ǘ����Ă�Memory�T�C�Y
ptr_size_t TLSFMemoryAllocator::GetHeapSize(){
    return this->m_memory_size;
}

//�g�p����Memory�T�C�Y
ptr_size_t TLSFMemoryAllocator::GetUseHeapSize(){
    return this->m_use_memory_size;
}

//�f�o�b�O�p�R���p�N�V��������Ȃ��������̊m��
void* TLSFMemoryAllocator::DebugNew(ptr_size_t size, const char* file_name, u32 line){
    ptr_t master_ptr = (ptr_t)this->New(size + sizeof(Debug_Check_Header));
    ptr_t debug_ptr = master_ptr + size;
    Debug_Check_Header* header = (Debug_Check_Header*)debug_ptr;
    header->end_code = MEMORY::End_Code;
    header->file_name = file_name;
    header->line = line;
    (*this->mp_debug_map)[master_ptr] = (Debug_Check_Header*)debug_ptr;
    return (void*)master_ptr;
}

//�f�o�b�O�p�R���p�N�V��������Ȃ��z�񃁃����̊m��
void* TLSFMemoryAllocator::DebugNewArray(ptr_size_t size, const char* file_name, u32 line){
    ptr_t master_ptr = (ptr_t)this->NewArray(size + sizeof(Debug_Check_Header));
    ptr_t debug_ptr = master_ptr + size;
    Debug_Check_Header* header = (Debug_Check_Header*)debug_ptr;
    header->end_code = MEMORY::End_Code;
    header->file_name = file_name;
    header->line = line;
    (*this->mp_debug_map)[master_ptr] = (Debug_Check_Header*)debug_ptr;
    return (void*)master_ptr;
}

                //�f�o�b�O�p�R���p�N�V��������Ȃ��������J��
void TLSFMemoryAllocator::DebugDelete(void* pointer){
    (*this->mp_debug_map).erase((ptr_t)pointer);
    this->Delete(pointer);
}
                //�f�o�b�O�p�R���p�N�V��������Ȃ��z�񃁃����J��
void TLSFMemoryAllocator::DebugDeleteArray(void* pointer){
    (*this->mp_debug_map).erase((ptr_t)pointer);
    this->Delete(pointer);
}

#include "../etc/evolution_debug.h"
void TLSFMemoryAllocator::DebugDataShow(){
    for (std::map<ptr_t, Debug_Check_Header*>::iterator it = (*this->mp_debug_map).begin(); it != (*this->mp_debug_map).end(); it++)
    {
        Debug::DebugPrint("%s(%d)\n endcode(%x)", it->second->file_name, it->second->line, it->second->end_code);
    }
}