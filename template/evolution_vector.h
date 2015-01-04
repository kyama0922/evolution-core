#ifndef __EVOLUTION_TEMPLATE_LIST_H_
#define __EVOLUTION_TEMPLATE_LIST_H_

#include <evolution_type.h>

namespace EVOLUTION{
	namespace TEMPLATE{
        //typedef int T;

		//�����R���e�i
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

            ////�x�N�^�ɗv�f�����蓖�Ă�
            //void assign(){
            //}

            //�w�肵���ʒu�̗v�f��Ԃ�
            T at(s32 index) {
                return mp_array[index];
            }

            //// �ŏI�v�f��Ԃ�
            //void back(){
            //
            //}
            //// �擪���w���C�e���[�^��Ԃ�
            //void begin(){
            //
            //}
            //// �x�N�^���ێ��ł���v�f��
            //void capacity(){

            //}

            // �S�Ă̗v�f���폜����
            void clear(){
                this->m_use_array_count = 0;
            }
            // �x�N�^����Ȃ�^
            bool empty(){
                return this->mp_array == nullptr;
            }
            //// �������w���C�e���[�^��Ԃ�
            //void end(){

            //}
            ////�v�f���폜����
            //void erase() {

            //}
            ////�擪�v�f��Ԃ�
            //void front() {

            //}
            ////�v�f���x�N�^�ɑ}������
            //void insert() {

            //}
            //�x�N�^���ێ��ł���ő�v�f����Ԃ�
            u32 max_size() {
                return this->m_max_array_count;
            }
            // �ŏI�v�f���폜����
            void pop_back(){
                if (0 < this->m_use_array_count){
                    this->m_use_array_count--;
                }
            }

            // �x�N�^�̖����ɗv�f��ǉ�����
            void push_back(const T& val){
                if (this->m_max_array_count <= this->m_use_array_count){
                    this->reserve((1+this->m_max_array_count) * 2);
                }
                this->mp_array[this->m_use_array_count++] = val;
            }

            ////�x�N�^�������w�����o�[�X�C�e���[�^��Ԃ�
            //void rbegin() {

            //}
            ////�x�N�^�擪���w�����o�[�X�C�e���[�^��Ԃ�
            //void rend() {

            //}

            // �x�N�^���ێ��ł���v�f����ݒ肷��
            void reserve(s32 size){
                this->m_max_array_count = size;
                T* work = NEW T[this->m_max_array_count];
                if (this->mp_array){
                    memcpy(work, this->mp_array, sizeof(T) * this->m_max_array_count);
                }
                EVOLUTION_DELETE_ARRAY(this->mp_array);
                this->mp_array = work;
            }

            //�x�N�^�̃T�C�Y��ύX����
            void resize(s32 size){
                this->m_use_array_count = size;
            }
            //�x�N�^���̗v�f����Ԃ�
            s32 size() {
                return this->m_use_array_count;
            }

            // ��̃x�N�^�����ւ���
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