#ifndef __EVOLUTION_TLSF_ALLOCATOR__
#define __EVOLUTION_TLSF_ALLOCATOR__

#include "evolution_memory_interface.h"
#include "tlsf-3.0/tlsf.h"
#
#include <map>
namespace EVOLUTION{
    namespace CORE{
        namespace MEMORY{

            static const u32 End_Code = 0x55555555;

            class TLSFMemoryAllocator : public IStaticMemoryManager{
            private:
                struct Debug_Check_Header{
                    u32 end_code;
                    u32 line;
                    const char* file_name;
                };

                EVOLUTION::InstanceCounter m_instance_counter;
                tlsf_t m_tlsf_instance;
                ptr_t mp_memory_pool;
                ptr_size_t m_memory_size;
                ptr_size_t m_use_memory_size;

                bool m_on_free;

                std::map<ptr_t, Debug_Check_Header*>* mp_debug_map;
            public:

                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                TLSFMemoryAllocator(ptr_size_t size);
                TLSFMemoryAllocator(ptr_t pointer, ptr_size_t size);

                ~TLSFMemoryAllocator();

                void Initialize();

                //コンパクションされないメモリの確保
                void* New(ptr_size_t size);
                //コンパクションされない配列メモリの確保
                void* NewArray(ptr_size_t size);
                //コンパクションされないノードの作成
                void Delete(void* pointer);
                //コンパクションされないノードの作成
                void DeleteArray(void* pointer);
                //管理してるMemoryサイズ
                ptr_size_t GetHeapSize();
                //使用中のMemoryサイズ
                ptr_size_t GetUseHeapSize();
                //デバッグ用コンパクションされないメモリの確保
                void* DebugNew(ptr_size_t size, const char* file_name, u32 line);
                //デバッグ用コンパクションされない配列メモリの確保
                void* DebugNewArray(ptr_size_t size, const char* file_name, u32 line);
                //デバッグ用コンパクションされないメモリ開放
                void DebugDelete(void* pointer);
                //デバッグ用コンパクションされない配列メモリ開放
                void DebugDeleteArray(void* pointer);

                void DebugDataShow();
            };

        }
    }

    namespace EVOLUTION_GUID{
        // {469E273C-EE33-4e4c-A151-AD851E137B67}
        static const EVOLUTION_IID IID_TLSFMemoryAllocator =
        { 0x469e273c, 0xee33, 0x4e4c, { 0xa1, 0x51, 0xad, 0x85, 0x1e, 0x13, 0x7b, 0x67 } };

    }
}


#endif //!__EVOLUTION_TLSF_ALLOCATOR__