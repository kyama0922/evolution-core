#ifndef __EVOLUTION_TEMPLATE_MAP_H_
#define __EVOLUTION_TEMPLATE_MAP_H_

#include <evolution_type.h>

#undef NEW
#ifndef NEW
#include <crtdbg.h>
#if _DEBUG
#define NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif
#endif

namespace EVOLUTION{
    namespace TEMPLATE{
        typedef u32 TValue;
        typedef u32 TKey;

        //template<class TKey, class TValue>
        class Map{
        public:
            struct Node{
                TKey m_key;
                TValue m_val;
            };

            //�C�e���[�^�[
            class iterator{
            public:
                Node* mp_node;//�m�[�h
                iterator* mp_parent;//�e�̃C�e���[�^
                iterator* mp_right;//�����̃C�e���[�^
                iterator* mp_left;//�E���̃C�e���[�^
                const Map* _map;

                iterator(const Map* map) :_map(map), mp_node(nullptr), mp_parent(nullptr), mp_left(nullptr), mp_right(nullptr)
                {
                    mp_node = nullptr;
                }

                iterator(const Map* map, Node* node) : _map(map), mp_node(node), mp_parent(nullptr), mp_left(nullptr), mp_right(nullptr)
                {

                }

                iterator(const Map* map, iterator* parent, Node* node) : _map(map), mp_node(node), mp_parent(parent), mp_left(nullptr), mp_right(nullptr)
                {

                }

                inline Node* operator->(){
                    return this->mp_node;
                }

                inline Node& operator*(){
                    return *this->mp_node;
                }

                inline iterator& operator=(const iterator& it){
                    this->mp_node = it.mp_node;
                    this->mp_left = it.mp_left;
                    this->mp_right = it.mp_right;
                    this->mp_parent = it.mp_parent;
                    return *this;
                }

                inline bool operator==(const iterator& it){
                    return it.mp_node->m_key == this->mp_node->m_key;
                }

                inline bool operator==(const iterator* it){
                    return it->mp_node->m_key == this->mp_node->m_key;
                }

                inline bool operator!=(const iterator& it){
                    return it.mp_node->m_key != this->mp_node->m_key;
                }

                inline iterator& operator++(int){

                    if (this->mp_right == nullptr)
                    {
                        TKey* key = &this->mp_node->m_key;
                        iterator* it = (this->mp_parent == nullptr) ? this : this->mp_parent;
                        while (true)
                        {
                            if (*key < it->mp_node->m_key)
                            {
                                break;
                            }
                            else if (it->mp_left != nullptr && it->mp_left != this->_map->mp_end &&  *key < it->mp_left->mp_node->m_key)
                            {
                                it = it->mp_left;
                                continue;
                            }
                            else if (it->mp_right != nullptr &&  *key < it->mp_right->mp_node->m_key)
                            {
                                it = it->mp_right;
                                continue;
                            }
                            
                            it = it->mp_parent;
                        }
                        *this = *it;
                    }
                    else{
                        TKey* key = &this->mp_node->m_key;
                        iterator* it = this->mp_right;
                        while (true)
                        {
                            if (it->mp_left != nullptr &&  *key < it->mp_left->mp_node->m_key)
                            {
                                it = it->mp_left;
                                continue;
                            }
                            break;
                        }
                        *this = *it;
                    }
                    return *this;
                }

                inline iterator& operator--(int){

                    if (this->mp_left == nullptr)
                    {
                        TKey* key = &this->mp_node->m_key;
                        iterator* it = this->mp_parent;
                        while (true)
                        {
                            if (it->mp_node->m_key < *key)
                            {
                                break;
                            }
                            else if (it->mp_left != nullptr &&  it->mp_left->mp_node->m_key < *key)
                            {
                                it = it->mp_left;
                                continue;
                            }
                            else if (it->mp_right != nullptr && it->mp_left != this->_map->mp_end && it->mp_right->mp_node->m_key < *key)
                            {
                                it = it->mp_right;
                                continue;
                            }
                            it = it->mp_parent;
                        }
                        *this = *it;
                    }
                    else{
                        TKey* key = &this->mp_node->m_key;
                        iterator* it = this->mp_left;
                        while (true)
                        {
                            if (it->mp_right != nullptr &&  it->mp_right->mp_node->m_key < *key)
                            {
                                it = it->mp_right;
                                continue;
                            }
                            break;
                        }
                        *this = *it;
                    }
                    return *this;
                }

                //inline iterator operator+(s32 num){
                //    iterator work_it = *this;
                //    for (u32 i = 0; i < num; i++)
                //    {
                //        if (this->mp_right == nullptr)
                //        {
                //            TKey* key = &work_it.mp_node->m_key;
                //            iterator* it = work_it.mp_parent;
                //            while (true)
                //            {
                //                if (*key < it->mp_node->m_key)
                //                {
                //                    break;
                //                }
                //                else if (it->mp_left != nullptr &&  *key < it->mp_left->mp_node->m_key)
                //                {
                //                    it = it->mp_left;
                //                    continue;
                //                }
                //                else if (it->mp_right != nullptr &&  *key < it->mp_right->mp_node->m_key)
                //                {
                //                    it = it->mp_right;
                //                    continue;
                //                }

                //                it = it->mp_parent;
                //            }
                //            return *it;
                //        }
                //        else{
                //            TKey* key = &work_it.mp_node->m_key;
                //            iterator* it = work_it.mp_right;
                //            while (true)
                //            {
                //                if (it->mp_left != nullptr &&  *key < it->mp_left->mp_node->m_key)
                //                {
                //                    it = it->mp_left;
                //                    continue;
                //                }
                //                break;
                //            }
                //            return *it;
                //        }
                //    }
                //    return work_it;
                //}

                //inline iterator operator-(s32 num){
                //    iterator work_it = *this;
                //    for (u32 i = 0; i < num; i++)
                //    {
                //        if (this->mp_left == nullptr)
                //        {
                //            TKey* key = &work_it.mp_node->m_key;
                //            iterator* it = work_it.mp_parent;
                //            while (true)
                //            {
                //                if (it->mp_node->m_key < *key)
                //                {
                //                    break;
                //                }
                //                else if (it->mp_left != nullptr &&  it->mp_left->mp_node->m_key < *key)
                //                {
                //                    it = it->mp_left;
                //                    continue;
                //                }
                //                else if (it->mp_right != nullptr &&  it->mp_right->mp_node->m_key < *key)
                //                {
                //                    it = it->mp_right;
                //                    continue;
                //                }
                //                it = it->mp_parent;
                //            }
                //            return *it;
                //        }
                //        else{
                //            TKey* key = &work_it.mp_node->m_key;
                //            iterator* it = work_it.mp_left;
                //            while (true)
                //            {
                //                if (it->mp_right != nullptr &&  it->mp_right->mp_node->m_key < *key)
                //                {
                //                    it = it->mp_right;
                //                    continue;
                //                }
                //                break;
                //            }
                //            return *it;
                //        }
                //    }
                //    return work_it;
                //}
            };

        public:
            u32 m_size;//�T�C�Y
            iterator* mp_root;//���[�g
            iterator* mp_end;//�G���h�|�C���^

            struct{
                u32 remove_0;
                u32 remove_1;
                u32 remove_2;
            }debug;
        public:

            Map() :m_size(0), mp_root(nullptr){
                this->mp_end = NEW iterator(this,NEW Node);
                this->mp_root = nullptr;
                memset(&debug, 0, sizeof(debug));
            }

            ~Map(){
                this->Clear();
                EVOLUTION_DELETE(this->mp_end->mp_node);
                EVOLUTION_DELETE(this->mp_end);
            }

            inline iterator Begin()
            {
                iterator* it = this->mp_root;
                while (it->mp_left != this->mp_end)
                {
                    it = it->mp_left;
                }
                return *it;
            }

            inline iterator Last()
            {
                iterator* it = this->mp_root;
                while (it->mp_right != this->mp_end)
                {
                    it = it->mp_right;
                }
                return *it;
            }

            inline iterator End()
            {
                return *this->mp_end;
            }

            inline iterator Find(const TKey& key)const{
                iterator* it = this->mp_root;
                while (true)
                {
                    iterator** pp_it;
                    bool right = false;
                    if (it->mp_node->m_key == key){
                        return *it;
                    }
                    else if (it->mp_node->m_key < key) {
                        pp_it = &it->mp_right;
                        right = true;
                    }
                    else{
                        pp_it = &it->mp_left;
                    }
                    //
                    if (*pp_it == this->mp_end || *pp_it == nullptr)
                    {
                        return iterator(this, this->mp_end->mp_node);
                    }
                    it = *pp_it;
                }
            }

            inline iterator Add(const TKey& key, const TValue& val){
                if (this->mp_root == nullptr)
                {
                    Node* node = NEW Node();
                    node->m_key = key;
                    node->m_val = val;
                    this->mp_root = NEW iterator(this, node);
                    this->mp_root->mp_left = this->mp_end;
                    this->mp_root->mp_right = this->mp_end;
                    this->m_size++;
                    return *this->mp_root;
                }

                //����key�Ȃ�l�����X�V

                iterator* it = this->mp_root;
                while (true)
                {
                    iterator** pp_it;
                    bool right = false;
                    if (it->mp_node->m_key == key){
                        it->mp_node->m_val = val;
                        return *it;
                    }
                    else if (it->mp_node->m_key < key) {
                        pp_it = &it->mp_right;
                        right = true;
                    }
                    else{
                        pp_it = &it->mp_left;
                    }
                    //
                    if (*pp_it == this->mp_end)
                    {
                        Node* node = NEW Node;
                        node->m_key = key;
                        node->m_val = val;
                        *pp_it = NEW iterator(this, it, node);
                        if (right){
                            (*pp_it)->mp_right = this->mp_end;
                            (*pp_it)->mp_left = nullptr;
                        }
                        else{
                            (*pp_it)->mp_right = nullptr;
                            (*pp_it)->mp_left = this->mp_end;
                        }
                        this->m_size++;
                        return **pp_it;
                    }
                    
                    if (*pp_it == nullptr){
                        Node* node = NEW Node;
                        node->m_key = key;
                        node->m_val = val;
                        *pp_it = NEW iterator(this, it, node);
                        if (right){
                            (*pp_it)->mp_right = nullptr;
                            (*pp_it)->mp_left = nullptr;
                        }
                        else{
                            (*pp_it)->mp_right = nullptr;
                            (*pp_it)->mp_left = nullptr;
                        }
                        this->m_size++;
                        return **pp_it;
                    }
                    it = *pp_it;
                }
                
            }

            inline  bool ContainsKey(const TKey& key)const{
                return this->Find(key) != *this->mp_end;
            }

            inline  void Remove(const TKey& key){
                iterator del_it = this->Find(key);
                if (del_it == this->mp_end)
                {
                    return;
                }
                bool end_ptr = false;
                //�m�[�h���ЂƂ������Ă��Ȃ��ꍇ
                if (del_it.mp_right == nullptr && del_it.mp_left == nullptr)
                {
                    if (del_it.mp_parent->mp_left != nullptr && del_it.mp_parent->mp_left->mp_node == del_it.mp_node)
                    {
                        EVOLUTION_DELETE(del_it.mp_parent->mp_left->mp_node);
                        EVOLUTION_DELETE(del_it.mp_parent->mp_left);
                    }
                    else
                    {
                        EVOLUTION_DELETE(del_it.mp_parent->mp_right->mp_node);
                        EVOLUTION_DELETE(del_it.mp_parent->mp_right);
                    }
                    debug.remove_0++;
                }
                //�m�[�h���ǂ��炩��̏ꍇ�܂��̓G���h�|�C���^�����Ă����ꍇ
                else if ((del_it.mp_right == this->mp_end || del_it.mp_left == this->mp_end) || del_it.mp_right == nullptr || del_it.mp_left == nullptr)
                {
                    end_ptr = (del_it.mp_right == this->mp_end || del_it.mp_left == this->mp_end);
                    //�G���h�|�C���^�̕t���ւ�
                    if (end_ptr)
                    {
                        bool rigth;
                        iterator** parent_node = (rigth = (del_it.mp_right == this->mp_end)) ? &del_it.mp_right : &del_it.mp_left;
                        //�G���h�|�C���^���O��
                        *parent_node = nullptr;
                        //�m�[�h�̍폜
                        if (del_it.mp_parent->mp_left != nullptr && del_it.mp_parent->mp_left->mp_node == del_it.mp_node)
                        {
                            EVOLUTION_DELETE(del_it.mp_parent->mp_left->mp_node);
                            EVOLUTION_DELETE(del_it.mp_parent->mp_left);
                        }
                        else
                        {
                            EVOLUTION_DELETE(del_it.mp_parent->mp_right->mp_node);
                            EVOLUTION_DELETE(del_it.mp_parent->mp_right);
                        }
                        if (rigth)
                        {
                            iterator* node = del_it.mp_left;
                            if (node == nullptr)
                            {
                                node = del_it.mp_parent;
                                while (node->mp_left == nullptr)
                                {
                                    node = node->mp_parent;
                                }
                            }
                            while (node->mp_right != nullptr && node->mp_right->mp_right != this->mp_end){
                                node = node->mp_right;
                            };
                            node->mp_right = this->mp_end;
                        }
                        else
                        {
                            iterator* node = del_it.mp_right;
                            if (node == nullptr)
                            {
                                node = del_it.mp_parent;
                                while (node->mp_right == nullptr)
                                {
                                    node = node->mp_parent;
                                }
                            }
                            while (node->mp_left != nullptr && node->mp_left->mp_left != this->mp_end){
                                node = node->mp_left;
                            };
                            node->mp_left = this->mp_end;
                        }
                        
                        this->m_size--;
                        return;
                    }
                    //�e�̎擾
                    iterator* parent = del_it.mp_parent;
                    //�e�̂ǂ���ɂȂ����Ă��邩����
                    iterator** parent_node = nullptr;
                    if (parent != nullptr){
                        parent_node = (parent->mp_right != nullptr && parent->mp_right->mp_node == del_it.mp_node) ? &parent->mp_right : &parent->mp_left;
                    }
                    //�m�[�h�f�[�^�̍폜
                    EVOLUTION_DELETE(del_it.mp_node);


                    if (del_it.mp_right != nullptr)
                    {
                        if (parent_node)
                        {
                            //�m�[�h�̍폜
                            EVOLUTION_DELETE(*parent_node);
                            //�m�[�h�̕t���ւ�
                            *parent_node = del_it.mp_right;
                            if (del_it.mp_right){
                                del_it.mp_right->mp_parent = parent;
                            }
                        }
                        else
                        {
                            //�e�����Ȃ��̂̓��[�g�Ȃ̂ō폜
                            EVOLUTION_DELETE(this->mp_root);
                            this->mp_root = del_it.mp_right;
                        }
                        
                    }
                    else{
                        if (parent_node)
                        {
                            //�m�[�h�̍폜
                            EVOLUTION_DELETE(*parent_node);
                            //�m�[�h�̕t���ւ�
                            *parent_node = del_it.mp_left;
                            if (del_it.mp_left){
                                del_it.mp_left->mp_parent = parent;
                            }
                        }
                        else
                        {
                            //�e�����Ȃ��̂̓��[�g�Ȃ̂ō폜
                            EVOLUTION_DELETE(this->mp_root);
                            this->mp_root = del_it.mp_left;
                        }
                        
                    }
                    debug.remove_1++;
                }
                else
                {
                    //�e�̎擾
                    iterator* parent = del_it.mp_parent;
                    //�e�̂ǂ���ɂȂ����Ă��邩����
                    iterator** parent_node = nullptr;
                    if (parent != nullptr)
                    {
                        parent_node = (parent->mp_right != nullptr && parent->mp_right->mp_node == del_it.mp_node) ? &parent->mp_right : &parent->mp_left;
                    }

                    iterator* node = del_it.mp_left;
                    
                    while (node->mp_right != nullptr){
                        node = node->mp_right;
                    };

                    //�m�[�h�̓���ւ�
                    node->mp_right = del_it.mp_right;
                    del_it.mp_right = nullptr;
                    //���̃m�[�h�̐e�̓���ւ�
                    node->mp_right->mp_parent = node;
                    //�m�[�h�̐e�ɘA�����Ă������������̃m�[�h�̍�����u��������
                    del_it.mp_parent->mp_right = node->mp_left;
                    del_it.mp_parent = nullptr;
                    //�����Ώۂ̃m�[�h�Ɠ���ւ���
                    if (node != del_it.mp_left)
                    {
                        node->mp_left = del_it.mp_left;
                    }
                    //�m�[�h�f�[�^�̍폜
                    EVOLUTION_DELETE(del_it.mp_node);
                    if (parent != nullptr)
                    {
                        EVOLUTION_DELETE(*parent_node);
                        *parent_node = node;
                    }
                    else
                    {
                        //�e�����Ȃ��̂̓��[�g�Ȃ̂ō폜
                        EVOLUTION_DELETE(this->mp_root);
                        this->mp_root = node;
                    }
                    node->mp_parent = parent;
                    debug.remove_2++;
                }
                this->m_size--;
            }

            inline void Clear(){

                iterator* it = this->mp_root;
                while (true)
                {
                    if (it->mp_left != nullptr && this->mp_end != it->mp_left)
                    {
                        it = it->mp_left;
                        continue;
                    }
                    else if (it->mp_right != nullptr && this->mp_end != it->mp_right)
                    {
                        it = it->mp_right;
                        continue;
                    }

                    
                    //�A���|�C���^�̍폜
                    if (it->mp_parent != nullptr)
                    {
                        iterator* parent = it->mp_parent;
                        if (parent->mp_right == it)
                        {
                            parent->mp_right = nullptr;
                        }
                        else if (parent->mp_left == it)
                        {
                            parent->mp_left = nullptr;
                        }
                        EVOLUTION_DELETE(it->mp_node);
                        EVOLUTION_DELETE(it);
                        it = parent;
                    }
                    else{
                        EVOLUTION_DELETE(it->mp_node);
                        EVOLUTION_DELETE(it);
                        break;
                    }
             
                }
                
            }

            //�z��A�N�Z�X
            inline TValue& operator[](const TKey& key){
                iterator it = this->Find(key);
                if (it == this->mp_end)
                {
                    it = this->Add(key, TValue());
                }
                return it->m_key;
            }

            inline u32 Size()
            {
                return this->m_size;
            }
        };
    }
}

#endif //!__EVOLUTION_TEMPLATE_ARRAY_H_