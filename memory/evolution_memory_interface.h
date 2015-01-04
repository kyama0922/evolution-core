#ifndef __EVOLUTION_MEMORY_INTERFACE__
#define __EVOLUTION_MEMORY_INTERFACE__

#include <evolution_type.h>

namespace EVOLUTION{
    namespace CORE{
        namespace MEMORY{

            struct MemoryException{
                enum _EXCEPTION{
                    CREATING_A_MEMORY_MANAGER_FAILURE,//メモリマネージャーの作成失敗
                    CREATE_SIZE_OVER,//作成管理サイズ以上になり確保できませんでした。
                };
            };

            class IDynamicMemoryManager;
            class IMemoryNode : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IMemoryNode);
            public:
                virtual RESULT GetMemoryManager(IDynamicMemoryManager** memory_manager)const = 0;
                virtual ptr_size_t GetSize()const = 0;
                virtual RESULT Lock(ptr_t* ref_data_ptr)const = 0;
                virtual RESULT Lock(void** ref_data_ptr)const = 0;
                virtual RESULT UnLock()const = 0;
            };

            class IDynamicMemoryManager : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IDynamicMemoryManager);
            public:
                //作成したNodeの数
                virtual ptr_size_t GetNodeNum() = 0;
                //ノードの作成
                virtual RESULT CreateMemoryNode(IMemoryNode** memory_node, u32 size) = 0;
                //ノードをCompactionする
                virtual RESULT Compaction() = 0;
                //管理してるMemoryサイズ
                virtual ptr_size_t GetHeapSize() = 0;
                //使用中のMemoryサイズ
                virtual ptr_size_t GetUseHeapSize() = 0;
            };


            class IStaticMemoryManager : public IUnknown{
                EVOLUTION_NOT_DESTRUCTOR(IStaticMemoryManager);
            public:
                //コンパクションされないメモリの確保
                virtual void* New(ptr_size_t size) = 0;
                //コンパクションされない配列メモリの確保
                virtual void* NewArray(ptr_size_t size) = 0;
                //コンパクションされないノードの作成
                virtual void Delete(void* pointer) = 0;
                //コンパクションされないノードの作成
                virtual void DeleteArray(void* pointer) = 0;
                //管理してるMemoryサイズ
                virtual ptr_size_t GetHeapSize() = 0;
                //使用中のMemoryサイズ
                virtual ptr_size_t GetUseHeapSize() = 0;

                //デバッグ用コンパクションされないメモリの確保
                virtual void* DebugNew(ptr_size_t size, const char* file_name, u32 line) = 0;
                //デバッグ用コンパクションされない配列メモリの確保
                virtual void* DebugNewArray(ptr_size_t size, const char* file_name, u32 line) = 0;

                //デバッグ用コンパクションされないメモリ開放
                virtual void DebugDelete(void* pointer) = 0;
                //デバッグ用コンパクションされない配列メモリ開放
                virtual void DebugDeleteArray(void* pointer) = 0;
                //デバッグ確保されているメモリ情報を表示
                virtual void DebugDataShow() = 0;
            };

            class IStackMemoryManager :public IUnknown{
            public:
                virtual void* Push(ptr_size_t size, ptr_size_t alignment = sizeof(ptr_t)) = 0;
                virtual void Pop(void* pointer) = 0;
                virtual void PopAll() = 0;

                template<class T>T* Push(ptr_size_t alignment = sizeof(ptr_t)){
                    return static_cast<T*>(this->Push(sizeof(T), alignment));
                }

                template<class T>T* PushArray(ptr_size_t array_size, ptr_size_t alignment = sizeof(ptr_t)){
                    return static_cast<T*>(this->Push(sizeof(T) * array_size, alignment));
                }
            };
        }
    }

    namespace FUNCTION{
        //メモリマネージャーの作成
        extern RESULT CreateTLSFStaticMemoryManager(CORE::MEMORY::IStaticMemoryManager** memory_manager, ptr_size_t size);
        //メモリマネージャーの作成
        extern RESULT CreateTLSFStaticMemoryManager(CORE::MEMORY::IStaticMemoryManager** memory_manager, ptr_t pointer, ptr_size_t size);

        //メモリマネージャー外の確保したメモリを渡す
        extern RESULT CreateDynamicMemoryManager(CORE::MEMORY::IDynamicMemoryManager** memory_manager, ptr_size_t size);
        //メモリマネージャー外の確保したメモリを渡す
        extern RESULT CreateDynamicMemoryManager(CORE::MEMORY::IDynamicMemoryManager** memory_manager, ptr_t pointer, ptr_size_t size);

        //メモリマネージャー外の確保したメモリを渡す
        extern RESULT CreateStackMemoryManager(CORE::MEMORY::IStackMemoryManager** memory_manager, ptr_size_t size);
        //メモリマネージャー外の確保したメモリを渡す
        extern RESULT CreateStackMemoryManager(CORE::MEMORY::IStackMemoryManager** memory_manager, ptr_t pointer, ptr_size_t size);
    }

    namespace EVOLUTION_GUID{
        // {EF090DDF-80E1-4a53-A807-1382282F9E2B}
        static const EVOLUTION_IID IID_IMemoryNode =
        { 0xef090ddf, 0x80e1, 0x4a53, { 0xa8, 0x7, 0x13, 0x82, 0x28, 0x2f, 0x9e, 0x2b } };

        // {7F6474B1-7F87-4a3d-98AE-31E31003DF5E}
        static const EVOLUTION_IID IID_IDynamicMemoryManager =
        { 0x7f6474b1, 0x7f87, 0x4a3d, { 0x98, 0xae, 0x31, 0xe3, 0x10, 0x3, 0xdf, 0x5e } };

        // {DA7EC383-E035-4071-9AA0-D4B90EB271D1}
        static const EVOLUTION_IID IID_IStaticMemoryManager =
        { 0xda7ec383, 0xe035, 0x4071, { 0x9a, 0xa0, 0xd4, 0xb9, 0xe, 0xb2, 0x71, 0xd1 } };

        // {3EA7C376-F537-40e9-8C6A-3EF82B77DF0E}
        static const EVOLUTION_IID IID_IStackMemoryManager =
        { 0x3ea7c376, 0xf537, 0x40e9, { 0x8c, 0x6a, 0x3e, 0xf8, 0x2b, 0x77, 0xdf, 0xe } };

    }

}
#endif //__EVOLUTION_MEMORY_INTERFACE__