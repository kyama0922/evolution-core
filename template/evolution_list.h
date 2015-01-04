#ifndef __EVOLUTION_TEMPLATE_LIST_H_
#define __EVOLUTION_TEMPLATE_LIST_H_

#include <evolution_type.h>

namespace EVOLUTION{
	namespace TEMPLATE{

		//順序コンテナ
		template<class T>
		class List{
		public:
			struct Node{
				T item;
				Node* mp_next;
				Node* mp_back;
			};
			//イテレーター
			class Iterator{
				friend List;
			private:
				Node* mp_node;
			public:
				Iterator() : mp_node(nullptr){}
				Iterator(Node* node) :mp_node(node){}
				Iterator(const Iterator& t){
					this->mp_node = t.mp_node;
				}

				const T& operator*() const{
					return this->mp_node->item;
				}

				T& operator*(){
					return this->mp_node->item;
				}
				const T& operator->() const{
					return this->mp_node->item;
				}
				T& operator->(){
					return this->mp_node->item;
				}
				const T& operator[](int n) const{
					Node* node = this->mp_node;
					for (s32 i = 0; i < n; i++)
					{
						if (node->mp_next != nullptr){
							node = node->mp_next;
						}
					}
					return node->item;
				}
				T& operator[](s32 n){
					Node* node = this->mp_node;
					for (s32 i = 0; i < n; i++)
					{
						if (node->mp_next != nullptr){
							node = node->mp_next;
						}
					}
					return node->item;
				}
				Iterator& operator++(){
					this->mp_node = this->mp_node->mp_next;
					return *this;
				}
				Iterator operator++(s32){
					this->mp_node = this->mp_node->mp_next;
					return *this;
				}
				Iterator& operator--(){
					this->mp_node = this->mp_node->mp_back;
					return *this;
				}
				Iterator operator--(s32){
					this->mp_node = this->mp_node->mp_back;
					return *this;
				}
                Iterator& operator+=(s32 n){
					for (s32 i = 0; i < n; i++)
					{
						if (this->mp_node->mp_next != nullptr){
							this->mp_node = this->mp_node->mp_next;
						}
					}
					return *this;
				}
                Iterator operator+(s32 n){
					for (s32 i = 0; i < n; i++)
					{
						if (this->mp_node->mp_next != nullptr){
							this->mp_node = this->mp_node->mp_next;
						}
					}
					return *this;
				}
                Iterator& operator-=(s32 n){
					for (s32 i = 0; i < n; i++)
					{
						if (this->mp_node->mp_back != nullptr){
							this->mp_node = this->mp_node->mp_back;
						}
					}
					return *this;
				}
                Iterator operator-(s32 n){
					for (s32 i = 0; i < n; i++)
					{
						if (this->mp_node->mp_back != nullptr){
							this->mp_node = this->mp_node->mp_back;
						}
					}
					return *this;
				}
				bool operator==(const Iterator& it) const{
					return this->mp_node == it.mp_node;
				}
				bool operator!=(const Iterator& it) const{
					return this->mp_node != it.mp_node;
				}
				bool operator>(const Iterator& it) const{
					Node* node = this->mp_node->mp_back;
					while (node->mp_back != nullptr)
					{
						if (node->mp_back == it.mp_node)
						{
							return true;
						}
						node = node->mp_back;
					}
					return false;
				}
				bool operator<(const Iterator& it) const{
					Node* node = this->mp_node->mp_next;
					while (node->mp_next != nullptr)
					{
						if (node->mp_next == it.mp_node)
						{
							return true;
						}
						node = node->mp_next;
					}
					return false;
				}
				bool operator>=(const Iterator& it) const{
					Node* node = this->mp_node;
					while (node->mp_back != nullptr)
					{
						if (node->mp_back == it.mp_node)
						{
							return true;
						}
						node = node->mp_back;
					}
					return false;
				}
				bool operator<=(const Iterator& it) const{
					Node* node = this->mp_node;
					while (node->mp_next != nullptr)
					{
						if (node->mp_next == it.mp_node)
						{
							return true;
						}
						node = node->mp_next;
					}
					return false;
				}
			};
		private:
			u32 m_size; //サイズ
			Iterator m_first;//先頭ノード
			Iterator m_last;//ラストノード
			Iterator m_end;//エンドポインタ
			Node* mp_end_node;//エンドノード
		public:
			List() :m_size(0){
				mp_end_node = NEW Node;
				this->mp_end_node->mp_back = nullptr;
				this->mp_end_node->mp_next = nullptr;
				this->m_end.mp_node = this->mp_end_node;
				this->m_first.mp_node = this->mp_end_node;
				this->m_last.mp_node = this->mp_end_node;
			}

			~List(){
				this->clear();
				EVOLUTION_DELETE(mp_end_node);
			}

            //最終要素の取得
			T back(){
				return this->m_last.mp_node->item;
			}

            //先頭のイテレーターの取得
			Iterator begin()const{
				return this->m_first;
			}
            
            //ノードの削除
			void clear(){
				while (this->m_size)
				{
					Node* node = this->m_first.mp_node->mp_next;
					if (this->m_first.mp_node != this->m_end.mp_node)
					{
						MONOBIT_DELETE(this->m_first.mp_node);
					}
					this->m_first.mp_node = node;
					this->m_size--;
				}

				this->m_first.mp_node = this->m_end.mp_node;
				this->m_last.mp_node = this->m_end.mp_node;
			}

            //コンテナが空かどうか
			bool empty()const{
				return this->m_size == 0;
			}

            //Endイテレーター
			const Iterator& end()const{
				return this->m_end;
			}

            //ノードの削除
			Iterator erase(Iterator pos){
				if (pos.mp_node->mp_next == &this->m_end_node)
				{
					MONOBIT_DELETE(pos.mp_node);
					this->m_size--;
					return Iterator(&this->m_end_node);
				}

				Node* node = pos.mp_node->mp_next;
				node->mp_back = pos.mp_node->mp_back;
				if (pos.mp_node->mp_back != &this->m_end_node){
					pos.mp_node->mp_back->mp_next = node;
				}
				if (pos == this->m_first)
				{
					this->m_first.mp_node = node;
				}
				else if (pos == this->m_end)
				{
					this->m_end.mp_node = node;
				}
				MONOBIT_DELETE(pos.mp_node);
				this->m_size--;
				return Iterator(node);
			}

            //ノードの削除
			Iterator erase(Iterator start, Iterator end){
				Iterator it;
				if (start <= end)
				{
					for (it = start; it != end;)
					{
						it = this->erase(it);
					}
				}
				else{
					for (it = start; it != end;)
					{
						Iterator remove_it = it;
						it--;
						this->erase(remove_it);
					}
				}
				return it;
			}

            //先頭のインスタンスの取得
			T front(){
				return this->m_first.mp_node->item;
			}

            //最終要素を削除する。
			void pop_back(){
				if (this->m_size == 0)
				{
					return;
				}

				Node* node = this->m_last.mp_node->mp_back;
				MONOBIT_DELETE(this->m_last.mp_node);

				node->mp_next = this->m_end.mp_node;
				this->m_last.mp_node = node;
				this->m_size--;

			}

            //先頭要素を削除する。 
			void pop_front(){
				if (this->m_size == 0)
				{
					return;
				}

				Node* node = this->m_first.mp_node->mp_next;
				MONOBIT_DELETE(this->m_first.mp_node);

				node->mp_back = this->m_end.mp_node;
				this->m_first.mp_node = node;
				this->m_size--;
			}

            //末尾に item を追加する
			void push_back(const T& item){
				Node* node = NEW Node;
				node->item = item;

				if (this->m_size == 0)
				{
					this->m_first.mp_node = node;
					this->m_last.mp_node = this->m_end.mp_node;
				}

				node->mp_back = this->m_last.mp_node;
				if (this->m_last.mp_node != this->m_end.mp_node)
				{
					this->m_last.mp_node->mp_next = node;
				}

				this->m_last.mp_node = node;
				node->mp_next = this->m_end.mp_node;
				this->m_size++;
			}

            //先頭に item を追加する
			void push_front(const T& item){
				Node* node = NEW Node;
				node->item = item;

				if (this->m_size == 0)
				{
					this->m_first.mp_node = this->m_end.mp_node;
					this->m_last.mp_node = node;
				}

				node->mp_next = this->m_first.mp_node;
				if (this->m_first.mp_node != this->m_end.mp_node)
				{
					this->m_first.mp_node->mp_back = node;
				}

				this->m_first.mp_node = node;
				node->mp_back = this->m_end.mp_node;
				this->m_size++;
			}


            //リストのサイズ
            u32 size(){
				return this->m_size;
			}

            //インスタンスの交換
			void swap(List& list){
				Node* end_node = this->mp_end_node;
				this->mp_end_node = list.mp_end_node;
				list.mp_end_node = end_node;

				Iterator swapit;
				swapit = this->m_first;
				this->m_first = list.m_first;
				list.m_first = swapit;

				swapit = this->m_last;
				this->m_last = list.m_last;
				list.m_last = swapit;

				swapit = this->m_end;
				this->m_end = list.m_end;
				list.m_end = swapit;

                u32 size = this->m_size;
				this->m_size = list.m_size;
				list.m_size = size;

			}
		};
	}
}

#endif //!__EVOLUTION_TEMPLATE_ARRAY_H_