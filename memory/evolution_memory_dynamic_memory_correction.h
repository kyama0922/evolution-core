#ifndef __EVOLUTION_DYNAMIC_MEMORY_ALLOCATOR__
#define __EVOLUTION_DYNAMIC_MEMORY_ALLOCATOR__

#include "evolution_memory_interface.h"

namespace EVOLUTION{
    namespace CORE{
        namespace MEMORY{

            typedef ptr_t MemoryHandler;

            //�ŏI�I�Ƀn���h���ɓn�����l
            struct MemoryHeader{
                //�|�C���^�[
                ptr_t pointer;
                //�������T�C�Y
                u32 size;
                //---------------------------------------------------------------------------
                //L: Lock�t���b�O(bit)
                //N: BlockNumber(����)(MAX:65536)
                //B: �u���b�N�g�p�Ԓn(����)(HIGH:LOW)(0:0) = 0 (1:1) = 5 (5:4) = 20 (7:4) = 32
                //0: ���g�p
                // | NNNN NNNN | NNNN NNNN | BBBB BBBB | 0000 000L |
                //---------------------------------------------------------------------------
                u32 flg;
            };

            //
            struct HeaderBlock{
                MemoryHeader handler[32];
                u32 use_bit;
            };

            class MemoryNode : public IMemoryNode{
            private:
                EVOLUTION::InstanceCounter m_instance_counter;
                MemoryHandler m_header;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();

                RESULT GetMemoryManager(IDynamicMemoryManager** memory_manager)const;
                ptr_size_t GetSize()const;
                RESULT Lock(ptr_t* ref_data_ptr)const;
                RESULT Lock(void** ref_data_ptr)const;
                RESULT UnLock()const;
            };

            class DynamicMemoryManager : public IDynamicMemoryManager{
            private:

                //�������v�[�����
                struct MemoryPool{
                    ptr_t pointer;
                    ptr_size_t size;
                    u32 memory_index;

                    MemoryHeader* header;
                    u32 header_count;
                    u32 header_index;
                };

                EVOLUTION::InstanceCounter m_instance_counter;

                ptr_t mp_pointer;
                ptr_size_t m_size;

                HeaderBlock* memory_;
            public:
                //IUnknown
                u32 AddRef();
                RESULT QueryInterface(EVOLUTION_IID riid, void **ppvObject);
                u32 Release();


                DynamicMemoryManager(ptr_size_t size);
                DynamicMemoryManager(ptr_t pointer, ptr_size_t size);
                ~DynamicMemoryManager();

                //�쐬����Node�̐�
                ptr_size_t GetNodeNum();
                //�m�[�h�̍쐬
                RESULT CreateMemoryNode(IMemoryNode** memory_node, ptr_size_t size);
                //�m�[�h��Compaction����
                RESULT Compaction();
                //�Ǘ����Ă�Memory�T�C�Y
                ptr_size_t GetHeapSize();
                //�g�p����Memory�T�C�Y
                ptr_size_t GetUseHeapSize();

                //�m�[�h�R���p�N�V�������b�N
                RESULT LockNodeResistor(IMemoryNode* node);
                //�m�[�h�R���p�N�V�����A�����b�N
                RESULT UnLockNodeResistor(IMemoryNode* node);
            };
        
        }
    }

    namespace EVOLUTION_GUID{
        // {AE039EFD-4E99-42d3-9C19-E547D8F4318C}
        static const EVOLUTION_IID IID_MemoryNode =
        { 0xae039efd, 0x4e99, 0x42d3, { 0x9c, 0x19, 0xe5, 0x47, 0xd8, 0xf4, 0x31, 0x8c } };

        // {4AA57596-941F-4ad2-A190-3E9669736BA5}
        static const EVOLUTION_IID IID_DynamicMemoryManager =
        { 0x4aa57596, 0x941f, 0x4ad2, { 0xa1, 0x90, 0x3e, 0x96, 0x69, 0x73, 0x6b, 0xa5 } };

    }
}


#endif//!__EVOLUTION_DYNAMIC_MEMORY_ALLOCATOR__