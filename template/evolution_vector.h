#ifndef __EVOLUTION_TEMPLATE_LIST_H_
#define __EVOLUTION_TEMPLATE_LIST_H_

#include <evolution_type.h>

namespace EVOLUTION{
	namespace TEMPLATE{
        //typedef int T;

		//順序コンテナ
		template<class T>
        class Vector{
        private:
            s32 m_max_array_count;
            s32 m_use_array_count;
            T* mp_array;
        public:
            Vector() :m_max_array_count(0), m_use_array_count(0), mp_array(nullptr){

            }

            Vector(s32 array_size) :m_max_array_count(array_size), m_use_array_count(0), mp_array(nullptr){
                mp_array = NEW T[array_size];
            }

            ~Vector(){
               EVOLUTION_DELETE_ARRAY(mp_array);
            }

            ////ベクタに要素を割り当てる
            //void assign(){
            //}

            //指定した位置の要素を返す
            T at(s32 index) {
                return mp_array[index];
            }

            //// 最終要素を返す
            //void back(){
            //
            //}
            //// 先頭を指すイテレータを返す
            //void begin(){
            //
            //}
            //// ベクタが保持できる要素数
            //void capacity(){

            //}

            // 全ての要素を削除する
            void clear(){
                this->m_use_array_count = 0;
            }
            // ベクタが空なら真
            bool empty(){
                return this->mp_array == nullptr;
            }
            //// 末尾を指すイテレータを返す
            //void end(){

            //}
            ////要素を削除する
            //void erase() {

            //}
            ////先頭要素を返す
            //void front() {

            //}
            ////要素をベクタに挿入する
            //void insert() {

            //}
            //ベクタが保持できる最大要素数を返す
            u32 max_size() {
                return this->m_max_array_count;
            }
            // 最終要素を削除する
            void pop_back(){
                if (0 < this->m_use_array_count){
                    this->m_use_array_count--;
                }
            }

            // ベクタの末尾に要素を追加する
            void push_back(const T& val){
                if (this->m_max_array_count <= this->m_use_array_count){
                    this->reserve((1+this->m_max_array_count) * 2);
                }
                this->mp_array[this->m_use_array_count++] = val;
            }

            ////ベクタ末尾を指すリバースイテレータを返す
            //void rbegin() {

            //}
            ////ベクタ先頭を指すリバースイテレータを返す
            //void rend() {

            //}

            // ベクタが保持できる要素数を設定する
            void reserve(s32 size){
                this->m_max_array_count = size;
                T* work = NEW T[this->m_max_array_count];
                if (this->mp_array){
                    memcpy(work, this->mp_array, sizeof(T) * this->m_max_array_count);
                }
                EVOLUTION_DELETE_ARRAY(this->mp_array);
                this->mp_array = work;
            }

            //ベクタのサイズを変更する
            void resize(s32 size){
                this->m_use_array_count = size;
            }
            //ベクタ中の要素数を返す
            s32 size() {
                return this->m_use_array_count;
            }

            // 二つのベクタを入れ替える
            void swap(Vector& t){
                this->mp_array = (T*)((ptr_t)t.mp_array ^ (ptr_t)this->mp_array);
                t.mp_array = (T*)((ptr_t)this->mp_array ^ (ptr_t)t.mp_array);
                this->mp_array = (T*)((ptr_t)t.mp_array ^ (ptr_t)this->mp_array);

                this->m_max_array_count = this->m_max_array_count ^ t.m_max_array_count;
                t.m_max_array_count = t.m_max_array_count ^ this->m_max_array_count;
                this->m_max_array_count = this->m_max_array_count ^ t.m_max_array_count;

                this->m_use_array_count = this->m_use_array_count ^ t.m_use_array_count;
                t.m_use_array_count = t.m_use_array_count ^ this->m_use_array_count;
                this->m_use_array_count = this->m_use_array_count ^ t.m_use_array_count;
            }

            T operator[](s32 index){
                return this->mp_array[index];
            }
        };
	}
}

#endif //!__EVOLUTION_TEMPLATE_ARRAY_H_