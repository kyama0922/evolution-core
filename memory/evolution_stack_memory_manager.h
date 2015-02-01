#ifndef __EVOLUTION_STACK_MEMORY_MANAGER_H__
#define __EVOLUTION_STACK_MEMORY_MANAGER_H__

#include <evolution_type.h>
#include "evolution_memory_interface.h"
namespace EVOLUTION{
    namespace CORE{
        namespace MEMORY{
            class StackMemoryManager :public IStackMemoryManager{
            private:
                struct FLAG{
                    enum{
                        MEMORY_DELETE = 0x00000001,//MEMORYをDeleteするフラグ
                    };
                };

                struct BLOCK_HEADER{
                    ptr_size_t endcode;
                    ptr_size_t offset;
                    ptr_size_t ptr_size;
                };
                EVOLUTION::InstanceCounter m_instance_counter;

                ptr_t m_pointer;
                ptr_t m_use_pointer;
                ptr_size_t m_memory_size;
                u32 m_flag;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION::EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                StackMemoryManager();
                ~StackMemoryManager();

                RESULT CreateMemory(ptr_size_t memory_size);
                RESULT CreateMemory(ptr_t pointer, ptr_size_t memory_size);

                void* Push(ptr_size_t size, ptr_size_t alignment = sizeof(ptr_t));
                void Pop(void* pointer);
                void PopAll();
            };
        }
    }
    namespace EVOLUTION_GUID{

        // {7C393E4B-67C9-4d20-BC70-50F4F811FEDB}
        static const EVOLUTION_IID IID_StackMemoryManager =
        { 0x7c393e4b, 0x67c9, 0x4d20, { 0xbc, 0x70, 0x50, 0xf4, 0xf8, 0x11, 0xfe, 0xdb } };

    }


}


#endif //!__EVOLUTION_STACK_MEMORY_MANAGER_H__