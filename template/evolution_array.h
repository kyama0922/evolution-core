#ifndef __EVOLUTION_TEMPLATE_ARRAY_H_
#define __EVOLUTION_TEMPLATE_ARRAY_H_

#include "../etc/evolution_assert.h"

namespace EVOLUTION{
    namespace TEMPLATE{
        //typedef u32 _T;
        template<class _T>
        class Array{
        private:
            u32 m_array_count;
            _T* mp_array;

            //�R�s�[�R���X�g���N�^�̋֎~
            Array(const Array& t) : mp_array(t.mp_array), m_array_count(t.m_array_count){
           
            }
        public:
            //�R���X�g���N�^
            Array() :m_array_count(0), mp_array(nullptr){

            }
            //�R���X�g���N�^�F�z��T�C�Y�̎w�肵�č쐬
            Array(u32 count) :m_array_count(count), mp_array(nullptr){
                this->mp_array = NEW _T[count];
            }

            //�f�X�g���N�^
            ~Array(){
                EVOLUTION_DELETE_ARRAY(this->mp_array);
            }

            //�z��̃T�C�Y�ύX(���̒l���j�������)
            inline void ReSize(u32 length){
                EVOLUTION_DELETE_ARRAY(this->mp_array);
                this->mp_array = NEW _T[length];
                m_array_count = length;
            }


            //�ő�T�C�Y�̎擾
            inline u32 GetMaxCount(){
                return this->m_array_count;
            }

            //�z��̃A�h���X�擾
            inline _T* GetArray(){
                return this->mp_array;
            }

            //�z��A�N�Z�X
            inline _T& operator[](u32 i){
                EVOLUTION_ASSERT(i < this->m_array_count);
                return mp_array[i];
            }

            //�N���X�̃R�s�[
            inline  Array<_T> Copy(){
                Array<_T> work(this->m_array_count);
                memcpy(work.mp_array, this->mp_array, sizeof(_T) * this->m_array_count);
                return work;
            }

            //�����o�̓���ւ�
            inline void Swap(Array& dest){
                _T* tmp_array = this->mp_array;
                u32 tmp_array_count = dest.m_array_count;

                this->mp_array = dest.mp_array;
                this->m_array_count = dest.m_array_count;

                dest.mp_array = tmp_array;
                dest.m_array_count = tmp_array_count;

            }

            //�����o�̓���ւ�
            inline void Set(u32 index , const _T& object){
                EVOLUTION_ASSERT(index < this->m_array_count);
                this->mp_array[index] = object;
            }

            //�����o�̓���ւ�
            inline void Set(const _T* pobject, u32 len){
                EVOLUTION_ASSERT(len <= this->m_array_count);
                memcpy(this->mp_array, pobject, sizeof(_T) * len);
            }
        };
    }
}

#endif //!__EVOLUTION_TEMPLATE_ARRAY_H_